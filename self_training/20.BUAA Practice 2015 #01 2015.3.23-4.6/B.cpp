#include <cstdio>
#include <cstring>
const int maxn = 10010, maxs = 15, maxk = 210;
int t, n, m, id[maxn], u[maxn], e[maxn][maxs], que[maxn], l, r, dis[maxn], res[maxn], tot, ans, pos;
bool vis[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(id, 0, sizeof id);
		memset(e, 0, sizeof e);
		memset(res, 0, sizeof res);
		memset(vis, 0, sizeof vis);
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", u + i);
			id[u[i]] = i;
			for(int j = 0; j <= e[i][0]; ++j)
				scanf("%d", e[i] + j);
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= e[i][0]; ++j)
				e[i][j] = id[e[i][j]];
		for(int i = 1; i <= m; ++i)
		{
			int p, s;
			scanf("%d", &s);
			for(int j = 1; j <= s; ++j)
			{
				scanf("%d", &p);
				vis[id[p]] = 1;
			}
		}
		for(int i = 1; i <= n; ++i)
		{
			if(!vis[i])
				continue;
			l = r = 0;
			memset(dis, 0, sizeof dis);
			que[r++] = i;
			dis[i] = 1;
			while(l < r)
			{
				int u = que[l++];
				for(int i = 1; i <= e[u][0]; ++i)
					if(!dis[e[u][i]])
					{
						que[r++] = e[u][i];
						dis[e[u][i]] = dis[u] + 1;
					}
			}
			for(int i = 1; i <= n; ++i)
				if(res[i] < dis[i])
					res[i] = dis[i];
		}
		ans = res[1];
		pos = u[1];
		for(int i = 2; i <= n; ++i)
			if(ans > res[i])
			{
				ans = res[i];
				pos = u[i];
			}
			else if(ans == res[i] && pos > u[i])
				pos = u[i];
		printf("%d %d\n", ans, pos);
	}
	return 0;
}
