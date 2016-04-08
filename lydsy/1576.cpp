#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 200001, maxd = 17;
struct Edge
{
	int nxt, u, v, w, ind;
	bool operator < (const Edge &x) const
	{
		return ind < x.ind;
	}
} e[maxm << 1];
int n, m, tot, pre[maxn], dis[maxn], dep[maxn], fa[maxn][maxd], nxt[maxn], ans[maxn];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
bool vis[maxn];
void dfs(int x)
{
	if(!dep[fa[x][0]])
		dfs(fa[x][0]);
	dep[x] = dep[fa[x][0]] + 1;
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
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[tot] = (Edge){pre[u], u, v, w, 0};
		pre[u] = tot++;
		e[tot] = (Edge){pre[v], v, u, w, 0};
		pre[v] = tot++;
	}
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	Q.push(make_pair(dis[1], 1));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = pre[u]; it != -1; it = e[it].nxt)
		{
			int &v = e[it].v, &w = e[it].w;
			if(dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	for(int u = 1; u <= n; ++u)
	{
		nxt[u] = u;
		for(int it = pre[u]; it != -1; it = e[it].nxt)
		{
			int &v = e[it].v, &w = e[it].w;
			if(dis[v] == dis[u] + w)
				fa[v][0] = u;
			else if(dis[u] != dis[v] + w && (it & 1))
				e[it].ind = dis[u] + dis[v] + w;
		}
	}
	dep[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(!dep[i])
			dfs(i);
	for(int d = 1; d < maxd; ++d)
		for(int i = 1; i <= n; ++i)
			fa[i][d] = fa[fa[i][d - 1]][d - 1];
	sort(e, e + tot);
	memset(ans, -1, sizeof ans);
	for(int it = 0; it < tot; ++it)
	{
		if(!e[it].ind)
			continue;
		int &u = e[it].u, &v = e[it].v, &w = e[it].ind, pp = lca(u, v);
		update(u, pp, w);
		update(v, pp, w);
	}
	for(int i = 2; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
