#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 1, maxd = 11, mod = 998244353;
int t, n, fact[maxn], c[maxn][maxn], f[maxn][maxd], g[maxn][maxd];
int main() {
	fact[0] = c[0][0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
	}
	scanf("%d", &t);
	while(t--) {
		int odd = 0, even = 0;
		scanf("%d", &n);
		memset(f[0], 0, sizeof f[0]);
		memset(g[0], 0, sizeof g[0]);
		f[0][0] = g[0][0] = 1;
		while(n--) {
			static char buf[maxd];
			scanf("%s", buf);
			int x = 0, len = strlen(buf);
			for(int i = 0; i < len; ++i) {
				int o = buf[i] - '0';
				(x += (len - i) & 1 ? o : maxd - o) >= maxd && (x -= maxd);
			}
			int &upp = len & 1 ? odd : even, (*F)[maxd] = len & 1 ? f : g;
			memset(F[++upp], 0, sizeof F[0]);
			for(int i = upp; i >= 0; --i) {
				static int G[maxd];
				for(int j = 0, p = x, q = x ? maxd - x : 0; j < maxd; ++j, (++p) == maxd && (p = 0), (++q) == maxd && (q = 0))
					(G[j] = F[i][p] + (i ? F[i - 1][q] : 0)) >= mod && (G[j] -= mod);
				memcpy(F[i], G, sizeof F[0]);
			}
		}
		int ans = 0, ec = odd >> 1, oc = odd - ec;
		if(odd) {
			for(int i = 0; i <= even; ++i) {
				int tmp = 0;
				for(int j = 0, k = 0; j < maxd; ++j, (--k) < 0 && (k += maxd))
					tmp = (tmp + (LL)f[oc][j] * g[i][k]) % mod;
				ans = (ans + (LL)tmp * fact[i] % mod * fact[even - i] % mod * c[ec + i][ec] % mod * c[oc - 1 + even - i][oc - 1]) % mod;
			}
		} else {
			ans = (LL)g[even][0] * fact[even] % mod;
		}
		ans = (LL)ans * fact[ec] % mod * fact[oc] % mod;
		printf("%d\n", ans);
	}
	return 0;
}