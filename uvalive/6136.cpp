#include <cstdio>
#include <cstring>
const int maxn = 610, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int n, g[maxn][maxn], que[maxn * maxn], l, r, ans;
bool vis[maxn][maxn];
char str[maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = -1;
		memset(g, 0, sizeof g);
		memset(vis, 0, sizeof vis);
		for(int i = 1; i < 2 * n; ++i)
		{
			scanf("%s", str);
			for(int j = 0; j < n; ++j)
				if(str[j] == 'H')
				{
					g[i][2 * j + 2 - (i & 1)] |= 4;
					g[i][2 * j + 3 - (i & 1)] |= 4;
					g[i + 1][2 * j + 2 - (i & 1)] |= 1;
					g[i + 1][2 * j + 3 - (i & 1)] |= 1;
				}
				else
				{
					g[i][2 * j + 2 - (i & 1)] |= 2;
					g[i][2 * j + 3 - (i & 1)] |= 8;
					g[i + 1][2 * j + 2 - (i & 1)] |= 2;
					g[i + 1][2 * j + 3 - (i & 1)] |= 8;
				}
		}
		for(int i = 1; i <= 2 * n + 1; ++i)
		{
			g[1][i] |= 1;
			g[2 * n][i] |= 4;
		}
		for(int i = 1; i <= 2 * n; ++i)
		{
			g[i][1] |= 8;
			g[i][2 * n + 1] |= 2;
		}
		for(int i = 1; i <= 2 * n; ++i)
			for(int j = 1; j <= 2 * n + 1; ++j)
				if(!vis[i][j])
				{
					++ans;
					l = r = 0;
					que[r++] = i * maxn + j;
					vis[i][j] = 1;
					while(l < r)
					{
						int x = que[l] / maxn, y = que[l] % maxn;
						for(int i = 0; i < 4; ++i)
							if(!(g[x][y] & (1 << i)) && !vis[x + dx[i]][y + dy[i]])
							{
								vis[x + dx[i]][y + dy[i]] = 1;
								que[r++] = (x + dx[i]) * maxn + y + dy[i];
							}
						++l;
					}
				}
		printf("%d\n", ans);
	}
	return 0;
}
