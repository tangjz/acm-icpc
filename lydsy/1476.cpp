#include <cstdio>
const int maxn = 1010, maxp = 100001;
int n, m, p, pos[maxn][maxn], fa[maxn][maxn], que[maxn * maxn], l, r, ans[maxp];
int find(int x, int y)
{
	return y == fa[x][y] ? y : fa[x][y] = find(x, fa[x][y]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= m; ++j)
			fa[i][j] = j;
	for(int t = 1, x1, y1, x2, y2; t <= p; ++t)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		--x1, --y1, --x2, --y2;
		for(int i = x1; i <= x2; ++i)
			for(int j = find(i, y1); j <= y2; j = find(i, j))
			{
				pos[i][j] = t;
				fa[i][j] = j + 1;
			}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(pos[i][j])
			{
				int idx = pos[i][j];
				++ans[idx];
				l = r = 0;
				que[r++] = i * m + j;
				pos[i][j] = 0;
				while(l < r)
				{
					int x = que[l] / m, y = que[l++] % m;
					if(x > 0 && pos[x - 1][y] == idx)
					{
						que[r++] = (x - 1) * m + y;
						pos[x - 1][y] = 0;
					}
					if(x < n - 1 && pos[x + 1][y] == idx)
					{
						que[r++] = (x + 1) * m + y;
						pos[x + 1][y] = 0;
					}
					if(y > 0 && pos[x][y - 1] == idx)
					{
						que[r++] = x * m + y - 1;
						pos[x][y - 1] = 0;
					}
					if(y < m - 1 && pos[x][y + 1] == idx)
					{
						que[r++] = x * m + y + 1;
						pos[x][y + 1] = 0;
					}
				}
			}
	for(int i = 1; i <= p; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
