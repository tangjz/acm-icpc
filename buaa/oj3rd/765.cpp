#include <cstdio>
#include <cstring>
int n, m, k, e[501][501], match[501], ans;
bool vis[501];
bool dfs(int u)
{
	for(int i = 1, v; i <= e[u][0]; ++i)
		if(!vis[v = e[u][i]])
		{
			vis[v] = 1;
			if(!match[v] || dfs(match[v]))
			{
				match[v] = u;
				return 1;
			}
		}
	return 0;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &k) == 3)
	{
		ans = 0;
		memset(e, 0, sizeof e);
		memset(match, 0, sizeof match);
		while(k--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			e[x][++e[x][0]] = y;
		}
		for(int i = 1; i <= n; ++i)
		{
			memset(vis, 0, sizeof vis);
			if(dfs(i))
				++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
