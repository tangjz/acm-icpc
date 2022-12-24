#include <stdio.h>
typedef long long LL;
const int maxn = 1001, maxm = 1000001, mod = 1000000007;
int t, r, c, m, f[maxn], g[maxn], fact[maxm], iact[maxm];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxm; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxm; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &r, &c, &m);
		if(c == 1) {
			printf("%d\n", mod_pow(m, r));
			continue;
		}
		g[0] = c == 2;
		for(int i = 1; i <= r; ++i) {
			f[i] = mod_pow(i, r);
			g[i] = mod_pow(f[i], c - 2);
		}
		for(int i = r; i > 0; --i) {
			f[i] = (LL)f[i] * iact[i] % mod;
			for(int j = 1; j < i; ++j) {
				int val = (LL)f[j] * iact[j] % mod * iact[i - j] % mod;
				if(val && ((i - j) & 1))
					val = mod - val;
				(f[i] += val) >= mod && (f[i] -= mod);
			}
			f[i] = (LL)f[i] * fact[i] % mod;
		}
		int ans = 0;
		for(int i = 1; i <= r; ++i) {
			int tmp = 0;
			for(int j = 0; j <= i; ++j) {
				int rem = m - (i << 1) + j;
				if(rem < 0)
					continue;
				tmp = (tmp + (LL)g[j] * iact[j] % mod * iact[i - j] % mod * iact[i - j] % mod * iact[rem]) % mod;
			}
			ans = (ans + (LL)f[i] * f[i] % mod * tmp) % mod;
		}
		ans = (LL)ans * fact[m] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
