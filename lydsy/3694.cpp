#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 4001, maxm = 100001, maxd = 13;
struct Edge
{
	int nxt, u, v, w, t;
	bool operator < (const Edge &x) const
	{
		return t < x.t;
	}
} e[maxm << 1];
int n, m, tot, pre[maxn], dis[maxn], dep[maxn], fa[maxn][maxd], nxt[maxn], ans[maxn];
void dfs(int u)
{
	for(int it = pre[u]; it != -1; it = e[it].nxt)
	{
		int &v = e[it].v, &w = e[it].w, &t = e[it].t;
		if(!t && !dep[v])
		{
			dis[v] = dis[u] + w;
			dep[v] = dep[u] + 1;
			fa[v][0] = u;
			dfs(v);
		}
	}
}
int lca(int u, int v)
{
	if(dep[u] > dep[v])
		swap(u, v);
	for(int i = 0, j = dep[v] - dep[u]; j; ++i, j >>= 1)
		if(j & 1)
			v = fa[v][i];
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int find(int x)
{
	return x == nxt[x] ? x : nxt[x] = find(nxt[x]);
}
void update(int u, int v, int w)
{
	for(int i = find(u); dep[i] > dep[v]; i = find(i))
	{
		ans[i] = w - dis[i];
		nxt[i] = fa[i][0];
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(pre, -1, sizeof pre);
	while(m--)
	{
		int u, v, w, t;
		scanf("%d%d%d%d", &u, &v, &w, &t);
		e[tot] = (Edge){pre[u], u, v, w, t ^ 1};
		pre[u] = tot++;
		e[tot] = (Edge){pre[v], v, u, w, t ^ 1};
		pre[v] = tot++;
	}
	dep[1] = 1;
	dfs(1);
	for(int u = 1; u <= n; ++u)
	{
		nxt[u] = u;
		for(int it = pre[u]; it != -1; it = e[it].nxt)
		{
			int &v = e[it].v, &w = e[it].w, &t = e[it].t;
			if(t)
				e[it].t = it & 1 ? dis[u] + dis[v] + w : 0;
		}
	}
	for(int d = 1; d < maxd; ++d)
		for(int i = 1; i <= n; ++i)
			fa[i][d] = fa[fa[i][d - 1]][d - 1];
	sort(e, e + tot);
	memset(ans, -1, sizeof ans);
	for(int it = 0; it < tot; ++it)
	{
		if(!e[it].t)
			continue;
		int &u = e[it].u, &v = e[it].v, &w = e[it].t, pp = lca(u, v);
		update(u, pp, w);
		update(v, pp, w);
	}
	for(int i = 2; i <= n; ++i)
		printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}
