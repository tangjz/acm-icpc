#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1, maxd = 19;
int n, m, a[maxn], lnk[maxn], f[maxn], g[maxn], old_f[maxn], st[maxd][maxn];
LL tot, sz[maxn], old_sz[maxn], sum[maxn], ans;
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
void reset(int u) {
	st[0][u] = f[u];
	for(int d = 1; d < maxd; ++d)
		st[d][u] = st[d - 1][st[d - 1][u]];
}
void dfs1(int u, int p) {
	f[u] = g[u] = 0;
	sz[u] = a[u];
	sum[u] = 0;
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == p)
			continue;
		dfs1(v, u);
		sz[u] += sz[v];
		sum[u] += sum[v] + sz[v];
		if(sz[f[u]] < sz[v]) {
			g[u] = f[u];
			f[u] = v;
		} else if(sz[g[u]] < sz[v]) {
			g[u] = v;
		}
	}
	reset(u);
}
void dfs2(int u, int p) {
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == p)
			continue;
		sum[v] += sum[u] - sum[v] - sz[v] + tot - sz[v];
		dfs2(v, u);
	}
}
inline pair<int, int> check(int u) {
	int p = u, c = 0;
	for(int d = maxd - 1; d >= 0; --d)
		if((sz[st[d][p]] << 1) > sz[u]) {
			p = st[d][p];
			c += 1 << d;
		}
	return make_pair(p, c);
}
void dfs3(int u, int p) {
	old_f[u] = f[u];
	old_sz[u] = sz[u];
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == p)
			continue;
		sz[u] = tot - sz[v];
		f[u] = v == old_f[u] ? g[u] : old_f[u];
		if(sz[f[u]] < tot - old_sz[u])
			f[u] = p;
		reset(u);
		pair<int, int> inner = check(v), outer = check(u);
		ans = min(ans, sum[inner.first] + sum[outer.first] - sum[u]
			- (tot - sz[v]) * (inner.second + 1) - sz[v] * outer.second);
		dfs3(v, u);
	}
	f[u] = old_f[u];
	sz[u] = old_sz[u];
	reset(u);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[++m] = (Edge){lnk[u], v};
		lnk[u] = m;
		e[++m] = (Edge){lnk[v], u};
		lnk[v] = m;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	dfs1(1, -1);
	tot = sz[1];
	dfs2(1, -1);
	ans = sum[1];
	dfs3(1, -1);
	printf("%lld\n", ans);
	return 0;
}
