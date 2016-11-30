#include <cstdio>
const int maxn = 101, maxm = 10001, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int n, m, que[maxm], deg[maxm], L, R;
char str[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str[i]);
		for(int j = 0; j < m; ++j)
			if(str[i][j] == '.')
				que[R++] = i * m + j;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if((i == 0 || i == n - 1 || j == 0 || j == m - 1) && str[i][j] != '.')
			{
				que[R] = i * m + j;
				deg[que[R++]] = 1;
			}
	while(L < R)
	{
		int x = que[L] / m, y = que[L] % m;
		for(int i = 0; i < 4; ++i)
		{
			int xx = x + dx[i], yy = y + dy[i];
			if(xx >= 0 && xx < n && yy >= 0 && yy < m && str[xx][yy] != '.' && !deg[xx * m + yy])
			{
				que[R] = xx * m + yy;
				deg[que[R++]] = deg[que[L]] + 1;
			}
		}
		++L;
	}
	int lim = deg[que[R - 1]] < 10 ? 2 : 3;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			if(!deg[i * m + j])
				for(int o = 0; o < lim; ++o)
					putchar('.');
			else
			{
				for(int o = 0; o < lim - 1 - (deg[i * m + j] >= 10); ++o)
					putchar('.');
				printf("%d", deg[i * m + j]);
			}
		putchar('\n');
	}
	return 0;
}
