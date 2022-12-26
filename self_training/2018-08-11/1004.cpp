#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 1, mod = 998244353;
int fact[maxn], iact[maxn], pw2[maxn], c[maxn][maxn];
int n, m, f[maxn], g[maxn];
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = pw2[0] = c[0][0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
		(pw2[i] = pw2[i - 1] << 1) >= mod && (pw2[i] -= mod);
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
	}
	while(scanf("%d%d", &n, &m) == 2) {
		memset(f, 0, (n + 1) * sizeof(int));
		for(int i = 0; i <= n; ++i)
			f[i] = (LL)fact[(n << 1) - i] * iact[i] % mod * fact[n] % mod * iact[n - i] % mod * pw2[i] % mod;
		for(int i = n; i >= 0; --i) {
			LL tmp = 0;
			for(int j = n; j > i; --j) {
				tmp += (LL)c[j][i] * g[j];
				if(tmp < 0)
					tmp = (unsigned long long)tmp % mod;
			}
			(g[i] = (f[i] - tmp) % mod) < 0 && (g[i] += mod);
		}
		int ans = 0, prd = 1;
		for(int i = 0; i <= n; ++i, prd = (LL)prd * m % mod) {
			ans = (ans + (LL)g[i] * prd) % mod;
//			printf("%d%c", g[i], " \n"[i == n]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
