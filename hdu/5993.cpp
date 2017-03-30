#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010, maxd = 18;
int tot, lnk[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
int t, n, m, Log[maxn << 1], dep[maxn], seq[maxn << 1], pos[maxn], Dist[maxn], st[maxd][maxn << 1];
int dfs_tot, que[maxn], in[maxn], out[maxn];
inline void dfs(int u, int fa)
{
	que[++dfs_tot] = u;
	in[u] = dfs_tot;
	seq[++tot] = u;
	pos[u] = tot;
	for(int it = lnk[u]; it; it = e[it].nxt)
	{
		int v = e[it].v, w = e[it].w;
		if(v == fa)
			continue;
		dep[v] = dep[u] + 1;
		Dist[v] = Dist[u] + w;
		dfs(v, u);
		seq[++tot] = u;
	}
	out[u] = dfs_tot;
}
inline int deepless(int u, int v)
{
	return dep[seq[u]] < dep[seq[v]] ? u : v;
}
inline int lca(int u, int v)
{
	register int L = pos[u], R = pos[v];
	if(L > R)
		swap(L, R);
	register int d = Log[R - L + 1];
	return seq[deepless(st[d][L], st[d][R - (1 << d) + 1])];
}
inline int dist(int u, int v)
{
	return Dist[u] + Dist[v] - 2 * Dist[lca(u, v)];
}
struct Seg {
	int u, v, w;
} seg[maxd][maxn];
inline Seg merge(Seg a, Seg b)
{
	register int dis;
	Seg ret = a.w < b.w ? b : a;
	if(ret.w < (dis = dist(a.u, b.u)))
		ret = (Seg){a.u, b.u, dis};
	if(ret.w < (dis = dist(a.u, b.v)))
		ret = (Seg){a.u, b.v, dis};
	if(ret.w < (dis = dist(a.v, b.u)))
		ret = (Seg){a.v, b.u, dis};
	if(ret.w < (dis = dist(a.v, b.v)))
		ret = (Seg){a.v, b.v, dis};
	return ret;
}
Seg query(int L, int R)
{
	register int d = Log[R - L + 1];
	return merge(seg[d][L], seg[d][R - (1 << d) + 1]);
}
inline int deepmore(int u, int v)
{
	return dep[u] < dep[v] ? v : u;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		tot = 0;
		memset(lnk + 1, 0, n * sizeof(int));
		for(int i = 1, u, v, w; i < n; ++i)
		{
			scanf("%d%d%d", &u, &v, &w);
			e[++tot].nxt = lnk[u];
			e[tot].v = v;
			e[tot].w = w;
			lnk[u] = tot;
			e[++tot].nxt = lnk[v];
			e[tot].v = u;
			e[tot].w = w;
			lnk[v] = tot;
		}
		tot = dfs_tot = 0;
		dfs(1, -1);
		for(int i = 2; i <= tot; ++i)
			Log[i] = Log[i >> 1] + 1;
		for(int i = 1; i <= tot; ++i)
			st[0][i] = i;
		for(int d = 1; d <= Log[tot]; ++d)
			for(int i = 1; i + (1 << (d - 1)) <= tot; ++i)
				st[d][i] = deepless(st[d - 1][i], st[d - 1][i + (1 << (d - 1))]);
		for(int i = 1; i <= n; ++i)
			seg[0][i] = (Seg){que[i], que[i], 0};
		for(int d = 1; d <= Log[n]; ++d)
			for(int i = 1; i + (1 << (d - 1)) <= n; ++i)
				seg[d][i] = merge(seg[d - 1][i], seg[d - 1][i + (1 << (d - 1))]);
		while(m--)
		{
			int i, j;
			scanf("%d%d", &i, &j);
			int u = deepmore(e[(i << 1) - 1].v, e[i << 1].v), v = deepmore(e[(j << 1) - 1].v, e[j << 1].v);
			if(in[u] > in[v])
				swap(u, v);
			Seg a, b, c;
			if(out[u] < in[v]) // two subtree
			{
				a = query(1, in[u] - 1);
				if(out[u] + 1 <= in[v] - 1)
					a = merge(a, query(out[u] + 1, in[v] - 1));
				if(out[v] + 1 <= n)
					a = merge(a, query(out[v] + 1, n));
				b = query(in[u], out[u]);
				c = query(in[v], out[v]);
			}
			else // v in u's subtree
			{
				a = query(1, in[u] - 1);
				if(out[u] + 1 <= n)
					a = merge(a, query(out[u] + 1, n));
				b = query(in[u], in[v] - 1);
				if(out[v] + 1 <= out[u])
					b = merge(b, query(out[v] + 1, out[u]));
				c = query(in[v], out[v]);
			}
			printf("%d\n", max(a.w, max(b.w, c.w)));
		}
	}
	return 0;
}
