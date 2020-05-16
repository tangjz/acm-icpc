#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1, mod = 998244353;
int n, f[maxn][2], sz[maxn], pw2[maxn];
vector<int> e[maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
void dfs(int u, int fa) {
	++sz[u];
	f[u][0] = 1;
	f[u][1] = 0;
	for(int v : e[u]) {
		if(v == fa)
			continue;
		dfs(v, u);
		sz[u] += sz[v];
		int sum = f[v][0];
		mod_inc(sum, f[v][1]);
		int nxt[2] = {};
		nxt[0] = (LL)f[u][0] * (sum + f[v][1]) % mod;
		nxt[1] = ((LL)f[u][0] * f[v][0] + (LL)f[u][1] * (sum + sum)) % mod;
		f[u][0] = nxt[0];
		f[u][1] = nxt[1];
	}
//	printf("%d: %d %d\n", u, f[u][0], f[u][1]);
}
int main() {
	pw2[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		pw2[i] = pw2[i - 1];
		mod_inc(pw2[i], pw2[i - 1]);
	}
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, -1);
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		ans = (ans + (LL)pw2[n - sz[i]] * f[i][1]) % mod;
	mod_inc(ans, ans);
	printf("%d\n", ans);
	return 0;
}