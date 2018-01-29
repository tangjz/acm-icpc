#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e7 + 1, mod = (int)1e9 + 7, inv9 = (mod + 1) / 9;
int tot, pr[maxn], d[maxn], Log[maxn];
int mod_inv(int x) {
    int y = mod, u = 1, v = 0, r;
    while(y) {
    	r = x / y;
    	swap(x, y);
    	y -= r * x;
    	swap(u, v);
    	v -= r * u;
    }
    assert(x == 1);
	return u < 0 ? u + mod : u;
}
int mod_pow(int x, LL k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main() {
	for(int i = 2, pw = 1, ex = 0; i < maxn; ++i) {
		if(!d[i]) {
			for( ; pw <= i; pw *= 10, ++ex);
			Log[tot] = ex;
			pr[tot++] = d[i] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int n;
	LL m;
	while(scanf("%d%lld", &n, &m) == 2) {
		int len = 0, pw = 1;
		int s0 = 0, s1 = 0, s2 = 0, s3 = 0;
		for(int i = n - 1; i >= 0; --i)
			for(int k = 0, val = pr[i]; k < Log[i]; ++k, val /= 10, ++len, pw = 10LL * pw % mod) {
				int dig = val % 10;
				(s0 += dig) >= mod && (s0 -= mod);
				s1 = (s1 + (LL)len * dig) % mod;
				s2 = (s2 + (LL)pw * dig) % mod;
				s3 = (s3 + (LL)len * pw % mod * dig) % mod;
			}
		int c0 = m % mod, c1 = c0 * (c0 + 1LL) / 2 % mod, c2, c3;
		if(pw == 1) {
			c2 = c0;
			c3 = c1;
		} else {
			int ivs = mod_inv(pw - 1);
			c2 = (LL)(mod_pow(pw, m) - 1) * ivs % mod;
			c3 = ((LL)pw * c2 - c0) % mod * ivs % mod;
		}
		int ans = (10LL * len % mod * c3 % mod * s2 - 10LL * c2 % mod * s3 - (LL)len * c1 % mod * s0 + (LL)c0 * s1) % mod * inv9 % mod;
		printf("%d\n", ans < 0 ? ans + mod : ans);
	}
	return 0;
}
