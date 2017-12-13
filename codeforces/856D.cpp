#include <bits/stdc++.h>
using namespace std;
typedef struct { int u, v, w; } Node;
const int maxn = (int)2e5 + 1, maxd = 19;
int n, m, tot, dep[maxn], mx, fa[maxd][maxn], in[maxn], out[maxn];
int bit[maxn], f[maxn], s[maxn];
vector<int> e[maxn];
vector<Node> g[maxn];
void pfs(int u) {
	in[u] = ++tot;
	for(auto &v : e[u]) {
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		pfs(v);
	}
	out[u] = tot;
}
int lca(int u, int v) {
	for(int i = dep[u] - dep[v], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (u = fa[j][u]);
	for(int i = dep[v] - dep[u], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (v = fa[j][v]);
	if(u == v)
		return u;
	for(int i = mx - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
void bit_add(int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
void dfs(int u) {
	for(auto &v : e[u]) {
		dfs(v);
		s[u] += f[v];
	}
	f[u] = s[u];
	for(auto &cur : g[u])
		f[u] = max(f[u], s[u] + bit_sum(in[cur.u]) + bit_sum(in[cur.v]) + cur.w);
	bit_add(in[u], s[u] - f[u]);
	bit_add(out[u] + 1, f[u] - s[u]);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 2; i <= n; ++i) {
		int p;
		scanf("%d", &p);
		e[p].push_back(i);
	}
	pfs(1);
	for( ; 1 << mx <= n; ++mx);
	for(int i = 1; i < mx; ++i)
		for(int j = 1; j <= n; ++j)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	while(m--) {
		Node cur;
		scanf("%d%d%d", &cur.u, &cur.v, &cur.w);
		g[lca(cur.u, cur.v)].push_back(cur);
	}
	dfs(1);
	printf("%d\n", f[1]);
	return 0;
}
