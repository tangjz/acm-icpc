#include <cstdio>
#include <cstring>
const int maxn = 1001;
int n, m, cnt, sum[maxn][maxn], ans = maxn * maxn;
char g[maxn][maxn];
bool vaild(int x1, int y1, int x2, int y2)
{
	if(x2 >= n || y2 >= m)
		return 0;
	int ret = sum[x2][y2];
	if(x1 && y1)
		ret += sum[x1 - 1][y1 - 1];
	if(x1)
		ret -= sum[x1 - 1][y2];
	if(y1)
		ret -= sum[x2][y1 - 1];
	return ret == (x2 - x1 + 1) * (y2 - y1 + 1);
}
bool check(int x, int y, int r, int c)
{
	if(!vaild(x, y, x + r - 1, y + c - 1))
		return 0;
	cnt = sum[n - 1][m - 1] - r * c;
	while(cnt)
	{
		bool down = vaild(x + r, y, x + r, y + c - 1), right = vaild(x, y + c, x + r - 1, y + c);
		if(down == right)
			return 0;
		if(down)
		{
			++x;
			cnt -= c;
		}
		else
		{
			++y;
			cnt -= r;
		}
	}
	return 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", g[i]);
		for(int j = 0; j < m; ++j)
		{
			sum[i][j] = g[i][j] == 'X';
			if(i)
				sum[i][j] += sum[i - 1][j];
			if(j)
				sum[i][j] += sum[i][j - 1];
			if(i && j)
				sum[i][j] -= sum[i - 1][j - 1];
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(g[i][j] == 'X')
			{
				int r, c;
				for(r = 0; i + r < n && g[i + r][j] == 'X'; ++r);
				for(c = 0; j + c < m && g[i][j + c] == 'X'; ++c);
				if(check(i, j, r, c) && ans > r * c)
					ans = r * c;
				for(int k = 1; k < r; ++k)
					if(check(i, j, k, c) && ans > k * c)
					{
						ans = k * c;
						break;
					}
				for(int k = 1; k < c; ++k)
					if(check(i, j, r, k) && ans > r * k)
					{
						ans = r * k;
						break;
					}
				if(ans == maxn * maxn)
					puts("-1");
				else
					printf("%d\n", ans);
				return 0;
			}
	puts("-1");
	return 0;
}
