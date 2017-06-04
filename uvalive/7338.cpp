#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10010, maxd = 15, maxm = 100010;
int t, n, m, dep[maxn], idx[maxn], fa[maxd][maxn], st[maxd][maxn];
int dsu[maxn], A[maxm], B[maxm], ord[maxm];
struct Edge
{
	int u, v, w;
} e[maxm];
vector<int> g[maxn];
bool cmp(const int &x, const int &y)
{
	return e[x].w < e[y].w;
}
void dfs(int u)
{
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
	{
		Edge &edge = e[*it];
		int v = edge.u == u ? edge.v : edge.u, w = edge.w;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		idx[v] = *it;
		fa[0][v] = u;
		st[0][v] = w;
		dfs(v);
	}
}
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
void upd(int id)
{
	int mx = 0, lca, u = e[id].u, v = e[id].v;
	if(dep[u] > dep[v])
		swap(u, v);
	for(int i = dep[v] - dep[u], d = 0; i; i >>= 1, ++d)
		if(i & 1)
		{
			upd(mx, st[d][v]);
			v = fa[d][v];
		}
	if(u == v)
		lca = u;
	else
	{
		for(int d = maxd - 1; d >= 0; --d)
			if(fa[d][u] != fa[d][v])
			{
				upd(mx, st[d][u]);
				u = fa[d][u];
				upd(mx, st[d][v]);
				v = fa[d][v];
			}
		upd(mx, st[0][u]);
		upd(mx, st[0][v]);
		lca = fa[0][u];
	}
	B[id] = e[id].w - mx;
	for(u = dsu_find(e[id].u); dep[u] > dep[lca]; u = dsu_find(u))
	{
		A[idx[u]] = e[id].w - e[idx[u]].w;
		dsu[u] = dsu_find(fa[0][u]);
	}
	for(u = dsu_find(e[id].v); dep[u] > dep[lca]; u = dsu_find(u))
	{
		A[idx[u]] = e[id].w - e[idx[u]].w;
		dsu[u] = dsu_find(fa[0][u]);
	}
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(g[i]);
		memset(dsu + 1, -1, n * sizeof(int));
		memset(A + 1, -1, m * sizeof(int));
		memset(B + 1, -1, m * sizeof(int));
		for(int i = 1; i <= m; ++i)
		{
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
			if(i >= n)
				ord[i] = i;
			else
			{
				g[e[i].u].push_back(i);
				g[e[i].v].push_back(i);
			}
		}
		dfs(1);
		for(int i = 1; i < maxd; ++i)
			for(int u = 1; u <= n; ++u)
			{
				int v = fa[i - 1][u];
				fa[i][u] = fa[i - 1][v];
				st[i][u] = max(st[i - 1][u], st[i - 1][v]);
			}
		sort(ord + n, ord + m + 1, cmp);
		for(int i = n; i <= m; ++i)
			upd(ord[i]);
		LL ans = 0;
		for(int i = 1; i <= m; ++i)
			ans += (B[i] * i + A[i]) * (LL)i;
		printf("Case %d: %lld\n", Case, ans);
	}
	return 0;
}
