#include <stdio.h>
const int maxn = (int)1e5 + 3, maxd = 17;
int n, m, lnk[maxn], nxt[maxn], fa[maxd][maxn], dep[maxn], in[maxn], out[maxn], bit[maxn];
void dfs(int u) {
	in[u] = ++n;
	for(int v = lnk[u]; v; v = nxt[v]) {
		dep[v] = dep[u] + 1;
		dfs(v);
	}
	out[u] = n;
}
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int i = m - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
void bit_add(int x) {
	for( ; x <= n; x += x & -x)
		++bit[x];
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 2, x; i <= n + 1; ++i) {
		scanf("%d", &x);
		nxt[i] = lnk[x];
		lnk[x] = i;
		fa[0][i] = x;
		for(int j = 1; fa[j - 1][i]; m < (++j) && (m = j))
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
	}
	n = 0;
	dfs(1);
	int rt = 1;
	long long ans = 0;
	bit_add(in[1]);
	for(int i = 2; i <= n; ++i) {
		bit_add(in[i]);
		ans += dep[rt] + dep[i] - (dep[lca(rt, i)] << 1);
		if(in[rt] <= in[i] && in[i] <= out[rt]) {
			int tr = i;
			for(int j = 0, k = dep[i] - dep[rt] - 1; k > 0; ++j, k >>= 1)
				(k & 1) && (tr = fa[j][tr]);
			int sz = bit_sum(out[tr]) - bit_sum(in[tr] - 1);
			if(sz > i - sz) {
				rt = tr;
				ans += (i - sz) - sz;
			}
		} else {
			int tr = fa[0][rt], sz = bit_sum(out[rt]) - bit_sum(in[rt] - 1);
			if(i - sz > sz) {
				rt = tr;
				ans += sz - (i - sz);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
