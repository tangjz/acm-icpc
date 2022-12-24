#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e4 + 1, maxd = 9;
int n, a[maxn], f[maxn], g[maxn], st[maxd][maxn];
vector<int> e[maxn];
LL tot, sz[maxn], sum[maxn], ans;
void reset(int u) {
	for(int d = 1; st[d][u]; ++d)
		st[d][u] = 0;
	st[0][u] = f[u];
	for(int d = 1; st[d - 1][u]; ++d)
		st[d][u] = st[d - 1][st[d - 1][u]];
}
void dfs1(int u, int p) {
	f[u] = g[u] = 0;
	sz[u] = a[u];
	sum[u] = 0;
	for(vector<int>::const_iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
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
	for(vector<int>::const_iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == p)
			continue;
		sum[v] += sum[u] - sum[v] - sz[v] + tot - sz[v];
		dfs2(v, u);
	}
}
pair<int, int> check(int u) {
	int d, p = u, c = 0;
	for(d = 0; st[d][u]; ++d);
	while((--d) >= 0)
		if((sz[st[d][p]] << 1) > sz[u]) {
			p = st[d][p];
			c += 1 << d;
		}
	return make_pair(p, c);
}
void dfs3(int u, int p) {
	int old_f = f[u];
	LL old_sz = sz[u];
	for(vector<int>::const_iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == p)
			continue;
		pair<int, int> inner = check(v);
		sz[u] = tot - sz[v];
		f[u] = v == old_f ? g[u] : old_f;
		if(sz[f[u]] < tot - old_sz)
			f[u] = p;
		reset(u);
		pair<int, int> outer = check(u);
		ans = min(ans, sum[inner.first] + sum[outer.first] - sum[u]
			- (tot - sz[v]) * (inner.second + 1) - sz[v] * outer.second);
		dfs3(v, u);
	}
	f[u] = old_f;
	sz[u] = old_sz;
	reset(u);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
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