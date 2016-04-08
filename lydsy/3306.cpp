#include <cstdio>
const int maxn = 131072, maxd = 17, INF = 0x3f3f3f3f;
int n, q, val[maxn], tot, pre[maxn], dep[maxn], fa[maxn][maxd], in[maxn], out[maxn], seg[maxn << 1], rt;
struct Edge
{
	int nxt, v;
} e[maxn];
int min(int x, int y)
{
	return x < y ? x : y;
}
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
void upd(int o, int L, int R, int x, int v)
{
	if(L == R)
	{
		seg[o] = v;
		return;
	}
	int M = L + R >> 1;
	if(x <= M)
		upd(o + o, L, M, x, v);
	else
		upd(o + o + 1, M + 1, R, x, v);
	seg[o] = min(seg[o + o], seg[o + o + 1]);
}
int que(int o, int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[o];
	int M = L + R >> 1;
	if(r <= M)
		return que(o + o, L, M, l, r);
	if(l > M)
		return que(o + o + 1, M + 1, R, l, r);
	return min(que(o + o, L, M, l, r), que(o + o + 1, M + 1, R, l, r));
}
void dfs(int u)
{
	in[u] = ++tot;
	upd(1, 1, n, in[u], val[u]);
	for(int it = pre[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v;
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		for(int d = 1; d < maxd; ++d)
			fa[v][d] = fa[fa[v][d - 1]][d - 1];
		dfs(v);
	}
	out[u] = tot;
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
int lcc(int u, int v)
{
	for(int i = 0, j = dep[v] - dep[u] - 1; j; ++i, j >>= 1)
		if(j & 1)
			v = fa[v][i];
	return v;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
	{
		int f;
		scanf("%d%d", &f, val + i);
		if(!f)
			rt = i;
		else
		{
			e[++tot] = (Edge){pre[f], i};
			pre[f] = tot;
		}
	}
	tot = 0;
	dfs(rt);
	for(int i = 1; i <= q; ++i)
	{
		char op[2];
		int x, y;
		scanf("%s%d", op, &x);
		if(op[0] == 'V')
		{
			scanf("%d", &y);
			upd(1, 1, n, in[x], y);
		}
		else if(op[0] == 'E')
			rt = x;
		else if(rt == x)
			printf("%d\n", seg[1]);
		else if(lca(x, rt) != x)
			printf("%d\n", que(1, 1, n, in[x], out[x]));
		else
		{
			y = lcc(x, rt);
			printf("%d\n", min(in[y] > 1 ? que(1, 1, n, 1, in[y] - 1) : INF, out[y] < n ? que(1, 1, n, out[y] + 1, n) : INF));
		}
	}
	return 0;
}
