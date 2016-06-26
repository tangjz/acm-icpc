#pragma comment(linker, "/STACK:102400000,102400000")  
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100010, maxd = 18;
int tot, lnk[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxn << 1];
int n, m, Log[maxn << 1], dep[maxn], seq[maxn << 1], pos[maxn], Dist[maxn], st[maxd][maxn << 1];
void dfs(int u, int fa)
{
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
}
inline int deepless(int u, int v)
{
	return dep[seq[u]] < dep[seq[v]] ? u : v;
}
inline int lca(int u, int v)
{
	int L = pos[u], R = pos[v];
	if(L > R)
		swap(L, R);
	int d = Log[R - L + 1];
	return seq[deepless(st[d][L], st[d][R - (1 << d) + 1])];
}
inline int dist(int u, int v)
{
	return Dist[u] + Dist[v] - 2 * Dist[lca(u, v)];
}
pair<int, int> seg[maxn << 1];
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
inline pair<int, int> merge(pair<int, int> a, pair<int, int> b, int flag = 0)
{
	int dis = -1, tmp;
	pair<int, int> ret;
	if(dis < (tmp = dist(a.first, b.first)))
	{
		ret = make_pair(a.first, b.first);
		dis = tmp;
	}
	if(dis < (tmp = dist(a.first, b.second)))
	{
		ret = make_pair(a.first, b.second);
		dis = tmp;
	}
	if(dis < (tmp = dist(a.second, b.first)))
	{
		ret = make_pair(a.second, b.first);
		dis = tmp;
	}
	if(dis < (tmp = dist(a.second, b.second)))
	{
		ret = make_pair(a.second, b.second);
		dis = tmp;
	}
	if(flag)
	{
		if(dis < (tmp = dist(a.first, a.second)))
		{
			ret = a;
			dis = tmp;
		}
		if(dis < (tmp = dist(b.first, b.second)))
		{
			ret = b;
			dis = tmp;
		}
	}
	return ret;
}
void build(int L, int R)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		seg[o] = make_pair(L, L);
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	seg[o] = merge(seg[lch], seg[rch], 1);
}
int qL, qR;
pair<int, int> query(int L, int R)
{
	if(qL <= L && R <= qR)
		return seg[seg_idx(L, R)];
	int M = L + R >> 1;
	pair<int, int> ret;
	if(qR <= M)
		ret = query(L, M);
	else if(qL > M)
		ret = query(M + 1, R);
	else
		ret = merge(query(L, M), query(M + 1, R), 1);
	return ret;
}
pair<int, int> query(int L, int R, int l, int r)
{
	qL = l;
	qR = r;
	return query(L, R);
}
int main()
{
	scanf("%d", &n);
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
	tot = 0;
	dfs(1, -1);
	for(int i = 2; i <= tot; ++i)
		Log[i] = Log[i >> 1] + 1;
	for(int i = 1; i <= tot; ++i)
		st[0][i] = i;
	for(int d = 1; d <= Log[tot]; ++d)
		for(int i = 1; i + (1 << d - 1) <= tot; ++i)
			st[d][i] = deepless(st[d - 1][i], st[d - 1][i + (1 << d - 1)]);
	build(1, n);
	scanf("%d", &m);
	while(m--)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		pair<int, int> s = query(1, n, a, b), t = query(1, n, c, d), r = merge(s, t);
		printf("%d\n", dist(r.first, r.second));
	}
	return 0;
}
