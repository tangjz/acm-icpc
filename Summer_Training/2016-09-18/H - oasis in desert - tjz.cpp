#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 510, INF = 0x3f3f3f3f;
int t, n, m, lim, g[maxn][maxn], col[maxn], dsu[maxn], cnt[maxn], tot, ans[maxn];
bool vis[maxn];
inline void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int dsu_find(int u)
{
	return dsu[u] < 0 ? u : dsu[u] = dsu_find(dsu[u]);
}
void dsu_merge(int u, int v)
{
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		dsu[v] = u;
	else if(dsu[u] > dsu[v])
		dsu[u] = v;
	else
	{
		dsu[v] = u;
		--dsu[u];
	}
}
bool dfs(int u)
{
	for(int v = 0; v < n; ++v)
		if(u != v && g[u][v] <= lim)
		{
			if(col[v] == -1)
			{
				dsu_merge(u, v);
				col[v] = 1 - col[u];
				if(!dfs(v))
					return 0;
			}
			else if(col[v] + col[u] != 1)
				return 0;
		}
	return 1;
}
int match[maxn];
bool p_vis[maxn];
bool path(int u)
{
	for(int v = 0; v < n; ++v)
		if(g[u][v] <= lim && col[u] + col[v] == 1 && !p_vis[v])
		{
			p_vis[v] = 1;
			if(match[v] == -1 || path(match[v]))
			{
				match[v] = u;
				return 1;
			}
		}
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &lim);
		for(int i = 0; i < n; ++i)
		{
			memset(g[i], 0x3f, n * sizeof(int));
			g[i][i] = 0;
		}
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u, --v;
			if(g[u][v] > w)
				g[u][v] = g[v][u] = w;
		}
		if(!n)
		{
			puts("0");
			continue;
		}
		/*
		if(n & 1)
		{
			puts("Impossible");
			continue;
		}
		*/
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					upd(g[i][j], g[i][k] + g[k][j]);
		memset(dsu, -1, n * sizeof(int));
		memset(col, -1, n * sizeof(int));
		bool flag = 1;
		for(int i = 0; i < n; ++i)
			if(col[i] == -1)
			{
				col[i] = 0;
				if(!dfs(i))
				{
					flag = 0;
					break;
				}
			}
		if(!flag)
		{
			puts("Impossible");
			continue;
		}
		memset(cnt, 0, n * sizeof(int));
		for(int i = 0; i < n; ++i)
			col[i] == 1 ? ++cnt[dsu_find(i)] : --cnt[dsu_find(i)];
		for(int i = 0; i < n; ++i)
			if(i == dsu_find(i) && cnt[i] != 0)
			{
				flag = 0;
				break;
			}
		if(!flag)
		{
			puts("Impossible");
			continue;
		}
		tot = 0;
		memset(vis, 0, n * sizeof(bool));
		memset(match, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i)
			if(!vis[i])
			{
				int color = col[i];
				for(int j = 0; j < n; ++j)
					if(dsu_find(j) == dsu_find(i) && col[j] == color)
					{
						memset(p_vis, 0, n * sizeof(bool));
						if(!path(j))
						{
							flag = 0;
							break;
						}
					}
				if(!flag)
					break;
				for(int j = 0; j < n; ++j)
					if(dsu_find(j) == dsu_find(i))
					{
						vis[j] = 1;
						if(col[j] == color)
							ans[tot++] = j;
					}
			}
		if(!flag)
		{
			puts("Impossible");
			continue;
		}
		sort(ans, ans + tot);
		printf("%d\n", tot);
		for(int i = 0; i < tot; ++i)
			printf("%d%c", ans[i] + 1, " \n"[i == tot - 1]);
	}
	return 0;
}
