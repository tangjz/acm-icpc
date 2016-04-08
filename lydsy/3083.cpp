#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 131072, INF = ~0u >> 1;
int n, m, a[maxn], s[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
int rt, dfs_t, in[maxn], out[maxn];
vector<int> e[maxn];
struct Segment
{
	int val, tag;
} seg[maxn << 1];
void pfs(int u)
{
	s[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(*it != fa[u])
		{
			fa[*it] = u;
			dep[*it] = dep[u] + 1;
			pfs(*it);
			if(s[*it] > s[son[u]])
				son[u] = *it;
			s[u] += s[*it];
		}
}
void push_down(int o)
{
	if(!seg[o].tag)
		return;
	seg[o + o].val = seg[o + o + 1].val = seg[o + o].tag = seg[o + o + 1].tag = seg[o].tag;
	seg[o].tag = 0;
}
void modify(int o, int L, int R, int l, int r, int val)
{
	if(l <= L && R <= r)
	{
		seg[o].val = seg[o].tag = val;
		return;
	}
	int M = L + R >> 1;
	push_down(o);
	if(l <= M)
		modify(o + o, L, M, l, r, val);
	if(r > M)
		modify(o + o + 1, M + 1, R, l, r, val);
	seg[o].val = min(seg[o + o].val, seg[o + o + 1].val);
}
void dfs(int u)
{
	in[u] = out[u] = ++dfs_t;
	modify(1, 1, n, in[u], out[u], a[u]);
	if(s[u] == 1)
		return;
	top[son[u]] = top[u];
	dfs(son[u]);
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(*it != fa[u] && *it != son[u])
		{
			top[*it] = *it;
			dfs(*it);
		}
	out[u] = dfs_t;
}
int query(int o, int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[o].val;
	int M = L + R >> 1, ret = INF;
	push_down(o);
	if(l <= M)
		ret = min(ret, query(o + o, L, M, l, r));
	if(r > M)
		ret = min(ret, query(o + o + 1, M + 1, R, l, r));
	return ret;
}
int lca(int u,int v, int w = -1)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]])
			swap(u, v);
		if(w != -1)
			modify(1, 1, n, in[top[u]], in[u], w);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v])
		swap(u, v);
	if(w != -1)
		modify(1, 1, n, in[u], in[v], w);
	return u;
}
int lcq(int u, int v)
{
	while(dep[fa[top[u]]] > dep[v])
		u = fa[top[u]];
	return fa[top[u]] == v ? top[u] : son[v];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	pfs(1);
	top[1] = 1;
	dfs(1);
	scanf("%d", &rt);
	while(m--)
	{
		int typ, u, v, w;
		scanf("%d", &typ);
		if(typ == 1)
			scanf("%d", &rt);
		else if(typ == 2)
		{
			scanf("%d%d%d", &u, &v, &w);
			lca(u, v, w);
		}
		else if(typ == 3)
		{
			scanf("%d", &u);
			if(u == rt)
			{
				printf("%d\n", seg[1].val);
				continue;
			}
			if(lca(u, rt) != u)
				printf("%d\n", query(1, 1, n, in[u], out[u]));
			else
			{
				v = lcq(rt, u);
				printf("%d\n", min(in[v] > 1 ? query(1, 1, n, 1, in[v] - 1) : INF, out[v] < n ? query(1, 1, n, out[v] + 1, n) : INF));
			}
		}
	}
	return 0;
}
