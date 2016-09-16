#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 50001, mod = 201314;
int n, m, tot, lnk[maxn], sz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], in[maxn], out[maxn];
struct Edge
{
	int nxt, v;
} e[maxn];
int bit[maxn][2], ans[maxn];
struct Query
{
	int idx, pos, val, sgn;
	bool operator < (const Query &t) const
	{
		return pos < t.pos;
	}
} que[maxn << 1];
void pfs(int u)
{
	sz[u] = 1;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
	{
		int v = e[it].v;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		pfs(v);
		if(son[u] == -1 || sz[son[u]] < sz[v])
			son[u] = v;
		sz[u] += sz[v];
	}
}
void dfs(int u)
{
	in[u] = ++tot;
	if(sz[u] > 1)
	{
		top[son[u]] = top[u];
		dfs(son[u]);
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].v != son[u])
			{
				top[e[it].v] = e[it].v;
				dfs(e[it].v);
			}
	}
	out[u] = tot;
}
void add(int x, int v)
{
	for(int t = x; t <= n; t += t & -t)
	{
		if((bit[t][0] += v) >= mod)
			bit[t][0] -= mod;
		if((bit[t][1] += v * x) >= mod)
			bit[t][1] -= mod;
	}
}
int sum(int x)
{
	int ret = 0;
	for(int t = x; t > 0; t -= t & -t)
		if((ret = (ret + (x + 1LL) * bit[t][0] - bit[t][1]) % mod) < 0)
			ret += mod;
	return ret;
}
void update(int x)
{
	for( ; x >= 0; x = fa[top[x]])
	{
		add(in[top[x]], 1);
		add(in[x] + 1, -1);
	}
}
int query(int x)
{
	int ret = 0;
	for( ; x >= 0; x = fa[top[x]])
	{
		if((ret += sum(in[x])) >= mod)
			ret -= mod;
		if((ret -= sum(in[top[x]] - 1)) < 0)
			ret += mod;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	memset(lnk, -1, n * sizeof(int));
	memset(son, -1, n * sizeof(int));
	for(int i = 1, j; i < n; ++i)
	{
		scanf("%d", &j);
		e[tot] = (Edge){lnk[j], i};
		lnk[j] = tot++;
	}
	fa[0] = -1;
	pfs(0);
	tot = 0;
	top[0] = 0;
	dfs(0);
	tot = 0;
	for(int i = 0; i < m; ++i)
	{
		int l, r, v;
		scanf("%d%d%d", &l, &r, &v);
		if(l)
			que[tot++] = (Query){i, l - 1, v, -1};
		que[tot++] = (Query){i, r, v, 1};
	}
	std::sort(que, que + tot);
	for(int i = 0, j = 0; i < n; ++i)
	{
		update(i);
		for( ; j < tot && que[j].pos == i; ++j)
			ans[que[j].idx] += query(que[j].val) * que[j].sgn;
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i] < 0 ? ans[i] + mod : ans[i]);
	return 0;
}
