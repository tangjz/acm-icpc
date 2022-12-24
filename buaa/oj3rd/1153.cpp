#include <cstdio>
#include <cstring>
const int maxn = 12;
int n, m, g[maxn][maxn];
bool flag;
void dfs(int x, int y)
{
	if(g[x][y] == 3)
	{
		flag = 1;
		return;
	}
	g[x][y] = 0;
	for(int i = -1; i <= 1 && !flag; ++i)
	{
		if(!flag && g[x + i][y])
			dfs(x + i, y);
		if(!flag && g[x][y + i])
			dfs(x, y + i);
	}
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(g, 0, sizeof g);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				scanf("%d", &g[i][j]);
				g[i][j] ^= 1;
			}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(g[i][j] == 2)
				{
					flag = 0;
					dfs(i, j);
					break;
				}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}
