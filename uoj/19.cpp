#include <cstdio>
#include <cstring>
const int maxn = 10001, maxm = 200001;
int n, m, s, t, tot, pre[maxn], suf[maxn], que[maxn], L, R, dis[maxn];
bool vis[maxn], g[maxn];
struct Edge
{
	int nxt, v;
} e[maxm << 1];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){pre[u], v};
		pre[u] = tot;
		e[++tot] = (Edge){suf[v], u};
		suf[v] = tot;
	}
	scanf("%d%d", &s, &t);
	que[R++] = t;
	vis[t] = 1;
	while(L < R)
	{
		int u = que[L++];
		for(int it = suf[u]; it; it = e[it].nxt)
			if(!vis[e[it].v])
			{
				que[R++] = e[it].v;
				vis[e[it].v] = 1;
			}
	}
	for(int u = 1; u <= n; ++u)
	{
		g[u] = 1;
		for(int it = pre[u]; it && g[u]; it = e[it].nxt)
			g[u] &= vis[e[it].v];
	}
	if(!g[s])
	{
		puts("-1");
		return 0;
	}
	L = R = 0;
	que[R++] = s;
	dis[s] = 1;
	while(L < R)
	{
		int u = que[L++];
		for(int it = pre[u]; it; it = e[it].nxt)
			if(g[e[it].v] && !dis[e[it].v])
			{
				que[R++] = e[it].v;
				dis[e[it].v] = dis[u] + 1;
			}
	}
	printf("%d\n", dis[t] - dis[s]);
	return 0;
}
