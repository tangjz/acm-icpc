#include <stdio.h>
#include <cstring>
const int maxn = 301, maxq = 100001, INF = 0x3f3f3f3f;
int n, m, q, e[maxn][maxn], ans[maxq];
bool vis[maxn];
struct Query
{
	int typ, x, y;
} query[maxq];
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		int u, v, w;
		memset(e, 0x3f, sizeof e);
		while(m--)
		{
			scanf("%d%d%d", &u, &v, &w);
			if(e[u][v] > w)
				e[u][v] = e[v][u] = w;
		}
		for(int i = 1; i <= n; ++i)
			e[i][i] = 0;
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < q; ++i)
		{
			scanf("%d%d", &w, &u);
			if(w)
			{
				scanf("%d", &v);
				query[i] = (Query){1, u, v};
			}
			else if(!vis[u])
			{
				query[i] = (Query){2, u};
				vis[u] = 1;
			}
			else
				query[i].typ = 0;
		}
		for(int i = 1; i <= n; ++i)
			if(!vis[i])
			{
				for(u = 1; u <= n; ++u) if(u != i && e[u][i] != INF)
					for(v = 1; v <= n; ++v) if(i != v && e[i][v] != INF)
						if(e[u][v] > e[u][i] + e[i][v])
							e[u][v] = e[u][i] + e[i][v];
			}
		for(int i = q - 1; i >= 0; --i)
			if(query[i].typ == 1)
				ans[i] = e[query[i].x][query[i].y];
			else if(query[i].typ == 2)
			{
				int &p = query[i].x;
				for(u = 1; u <= n; ++u) if(u != p && e[u][p] != INF)
					for(v = 1; v <= n; ++v) if(p != v && e[p][v] != INF)
						if(e[u][v] > e[u][p] + e[p][v])
							e[u][v] = e[u][p] + e[p][v];
			}
		for(int i = 0; i < q; ++i)
			if(query[i].typ == 1)
				printf("%d\n", ans[i] == INF ? -1 : ans[i]);
	}
	return 0;
}
