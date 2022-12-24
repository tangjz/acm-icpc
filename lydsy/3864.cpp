#include <bits/stdc++.h>
const int maxn = 17, maxs = 1 << 15 | 1, maxc = 4, mod = (int)1e9 + 7;
const char *pat = "ACGT";
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	static int bits[maxs];
	bits[0] = 0;
	for(int i = 1; i < maxs; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, m;
		static char buf[maxn];
		scanf("%s%d", buf, &m);
		for(n = 0; buf[n]; ++n);
		static int nxt[maxc + 1][maxs], *que = nxt[maxc];
		memset(nxt[0], -1, (1 << n) * sizeof(int));
		que[0] = nxt[0][0] = 0;
		for(int i = 0, tot = 1; i < tot; ++i) {
			int u = que[i];
			static int f[maxn], g[maxn];
			f[0] = 0;
			for(int j = 0, k = u; j < n; ++j, k >>= 1)
				f[j + 1] = f[j] + (k & 1);
			for(int j = 0; j < maxc; ++j) {
				int v = g[0] = 0;
				for(int k = 0; k < n; ++k)
					g[k + 1] = buf[k] == pat[j] ? f[k] + 1 : std::max(f[k + 1], g[k]);
				for(int k = n; k > 0; --k)
					v = v << 1 | (g[k] > g[k - 1]);
				nxt[j][u] = v;
				if(nxt[0][v] == -1) {
					nxt[0][v] = 0;
					que[tot++] = v;
				}
			}
		}
		static int o = 0, dp[2][maxs];
		memset(dp[o], 0, (1 << n) * sizeof(int));
		dp[o][0] = 1;
		for(int i = 0; i < m; ++i) {
			o = !o;
			memset(dp[o], 0, (1 << n) * sizeof(int));
			for(int j = 0; j < (1 << n); ++j)
				if(dp[!o][j])
					for(int k = 0; k < maxc; ++k)
						mod_inc(dp[o][nxt[k][j]], dp[!o][j]);
		}
		static int ans[maxn];
		memset(ans, 0, (n + 1) * sizeof(int));
		for(int i = 0; i < (1 << n); ++i)
			mod_inc(ans[bits[i]], dp[o][i]);
		for(int i = 0; i <= n; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}