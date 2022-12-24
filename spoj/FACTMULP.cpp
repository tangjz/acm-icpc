#include <bits/stdc++.h>
typedef long long LL;
const int mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int t;
LL n, m;
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld", &n, &m);
		if((n %= mod) == 1) {
			printf("%d\n", (int)(m % mod));
			continue;
		}
		int pw = mod_pow(n, m % (mod - 1)), ivs = mod_pow(n - 1, mod - 2);
		int ans = (((pw - 1LL) * ivs - m) % mod * pw % mod * inv2 + (pw - 1LL) * ivs) % mod;
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}