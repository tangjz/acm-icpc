#include <bits/stdc++.h>
typedef long long LL;
const int maxm = (int)1e3 + 1, mod = (int)1e9 + 7;
int n, m, inv[maxm + 2], f[maxm], g[maxm];
LL s, t;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main() {
	scanf("%lld%lld%d%d", &s, &t, &n, &m);
	if(!(t %= mod)) {
		puts("0");
		return 0;
	}
	s %= mod;
	m -= n;
	inv[1] = 1;
	for(int i = 2; i <= m + 1; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 0, ivs = 1; i <= m; ++i) {
		ivs = (LL)ivs * inv[i + 1] % mod;
		f[i] = 0;
		for(int j = i - 1; j >= 0; --j)
			f[i] = ((LL)f[i] * (i - j + 1LL) + f[j]) % mod;
		f[i] = (LL)(mod_pow(t + 1, i + 1) - 1 - f[i]) * ivs % mod;
		if(f[i] < 0)
			f[i] += mod;
	}
	g[0] = mod_pow(f[0], n);
	for(int i = 1, ivs = mod_pow(f[0], mod - 2); i <= m; ++i) {
		g[i] = (LL)n * i % mod * f[i] % mod * g[0] % mod;
		for(int j = 1; j < i; ++j)
			g[i] = (g[i] + ((LL)n * j - (i - j)) % mod * f[j] % mod * g[i - j]) % mod;
		g[i] = (LL)g[i] * inv[i] % mod * ivs % mod;
		if(g[i] < 0)
			g[i] += mod;
	}
	f[0] = 1;
	for(int i = 1; i <= m; ++i)
		f[i] = (LL)f[i - 1] * (mod - s) % mod * inv[i] % mod;
	for(int i = m; i >= 0; --i) {
		f[i] = (LL)g[0] * f[i] % mod;
		for(int j = 1; j <= i; ++j)
			f[i] = (f[i] + (LL)g[j] * f[i - j]) % mod;
	}
	g[0] = 1;
	for(int i = 0; i < m; ++i) {
		g[i + 1] = 0;
		for(int j = i + 1; j >= 0; --j) {
			g[j] = ((LL)g[j] * i + (j ? g[j - 1] : 0)) % mod;
			g[j] = (LL)(mod - g[j]) * inv[i + 1] % mod;
		}
	}
	int ans = 0;
	for(int i = m; i >= 0; --i)
		ans = (ans * (i + 1LL) + (LL)f[i] * g[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
