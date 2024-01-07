#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = (int)2e3 + 1, mod = 998244353;
int n, sz[maxn], f[maxn][2][maxn];
vector<int> e[maxn];
inline void mod_inc(LL &x, LL y) {
//	if((x += y) < 0)
//		x = (ULL)x % mod;
	x = (x + y) % mod;
}
inline void mod_add(int &x, int y) {
	x >= mod && (x %= mod);
	y >= mod && (y %= mod);
	(x += y) >= mod && (x -= mod);
}
void dfs(int u, int fa) {
	for(int v : e[u]) {
		if(v == fa)
			continue;
		dfs(v, u);
	}
	static LL g[6][maxn];
	sz[u] = 0;
	g[0][0] = 1;
	g[1][0] = g[2][0] = 0;
	for(int v : e[u]) {
		if(v == fa)
			continue;
		memset(g[3], 0, (sz[u] + sz[v] + 1) * sizeof(LL));
		memset(g[4], 0, (sz[u] + sz[v] + 1) * sizeof(LL));
		memset(g[5], 0, (sz[u] + sz[v] + 1) * sizeof(LL));
		for(int i = 0; i <= sz[u]; ++i)
			for(int j = 0; j <= sz[v]; ++j) {
				int sum = f[v][0][j] + f[v][1][j];
				mod_inc(g[3][i + j], (LL)g[0][i] * sum);
				mod_inc(g[4][i + j], (LL)g[0][i] * f[v][1][j] + (LL)g[1][i] * sum);
				mod_inc(g[5][i + j], (LL)g[1][i] * f[v][1][j] + (LL)g[2][i] * sum);
			}
		sz[u] += sz[v];
		memcpy(g[0], g[3], (sz[u] + 1) * sizeof(LL));
		memcpy(g[1], g[4], (sz[u] + 1) * sizeof(LL));
		memcpy(g[2], g[5], (sz[u] + 1) * sizeof(LL));
	}
	++sz[u];
	memset(f[u][0], 0, (sz[u] + 1) * sizeof(int));
	memset(f[u][1], 0, (sz[u] + 1) * sizeof(int));
	for(int i = 0; i < sz[u]; ++i) {
		g[0][i] >= mod && (g[0][i] %= mod);
		g[1][i] >= mod && (g[1][i] %= mod);
		g[2][i] >= mod && (g[2][i] %= mod);
		mod_add(f[u][0][i], (int)g[0][i]);
		if(i)
			mod_add(f[u][0][i - 1], (int)g[2][i]);
		mod_add(f[u][1][i + 1], (int)g[0][i]);
		mod_add(f[u][1][i], (int)g[1][i]);
	}
}
inline int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, -1);
	int prd = 1, ivs = mod_inv(n * (n + 1) / 2), ans = 0;
	for(int i = 1; i <= n; ++i) {
		prd = (LL)prd * i % mod * ivs % mod;
		ans = (ans + (LL)prd * (f[1][0][i] + f[1][1][i])) % mod;
	}
	printf("%d\n", ans);
	return 0;
}