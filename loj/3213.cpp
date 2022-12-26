#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, maxd = 19;
int t, n, sz[maxn], f[maxn], g[maxn], st[maxd][maxn];
vector<int> e[maxn];
LL ans;
void reset(int u) {
	for(int d = 1; st[d][u]; ++d)
		st[d][u] = 0;
	st[0][u] = f[u];
	for(int d = 1; st[d - 1][u]; ++d)
		st[d][u] = st[d - 1][st[d - 1][u]];
}
void pfs(int u, int p) {
	sz[u] = 1;
	f[u] = g[u] = 0;
	for(int v : e[u]) {
		if(v == p)
			continue;
		pfs(v, u);
		sz[u] += sz[v];
		if(sz[f[u]] < sz[v]) {
			g[u] = f[u];
			f[u] = v;
		} else if(sz[g[u]] < sz[v]) {
			g[u] = v;
		}
	}
	reset(u);
}
void check(int u) {
	int d, p = u;
	for(d = 0; st[d][u]; ++d);
	while((--d) >= 0)
		if((sz[st[d][p]] << 1) > sz[u])
			p = st[d][p];
	ans += p;
	if(st[0][p] && (sz[st[0][p]] << 1) >= sz[u])
		ans += st[0][p];
}
void dfs(int u, int p) {
	int old_sz = sz[u], old_f = f[u];
	for(int v : e[u]) {
		if(v == p)
			continue;
		check(v);
		sz[u] = n - sz[v];
		f[u] = v == old_f ? g[u] : old_f;
		if(sz[f[u]] < n - old_sz)
			f[u] = p;
		reset(u);
		check(u);
		dfs(v, u);
	}
	sz[u] = old_sz;
	f[u] = old_f;
	reset(u);
}
int main() {
	freopen("centroid.in", "r", stdin);
	freopen("centroid.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		pfs(1, -1);
		ans = 0;
		dfs(1, -1);
		printf("%lld\n", ans);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
