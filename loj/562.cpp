#include <bits/stdc++.h>
typedef long long LL;
const int mod = 998244353, sd = 19190506, per = 917504, lim = 1089914;
int f[per + 1], g[lim + 1];
int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	f[0] = 1;
	for(int i = 1, x = 1, y = 1, ivs = mod_inv(sd); i < per; ++i) {
		f[i] = (LL)f[i - 1] * y % mod;
		x = (LL)x * ivs % mod;
		(y += x) >= mod && (y -= mod);
	}
	g[0] = 1;
	for(int i = 1; i < lim; ++i)
		g[i] = (LL)g[i - 1] * i % mod;
	int t;
	LL n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld", &n, &m);
		int nL = n % per, nH = n / per;
		int mL = m % per, mH = m / per;
		if(nL < mL) {
			puts("0");
			continue;
		}
		int ans = (LL)mod_pow(sd, (LL)(nL - mL) * mL % per) * f[nL] % mod * mod_inv((LL)f[nL - mL] * f[mL] % mod) % mod;
		ans = (LL)ans * g[nH] % mod * mod_inv((LL)g[nH - mH] * g[mH] % mod) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
