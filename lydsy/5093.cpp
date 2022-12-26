#include <bits/stdc++.h>
typedef long long LL;
const int maxLen = 19, maxs = 1 << maxLen | 1, mod = 998244353, gen = 3, inv2 = (mod + 1) >> 1;
int w[maxs << 1 | 1];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? (x + mod) : x;
}
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void initNTT(int len) {
	int bitLen;
	for(bitLen = 0; (1 << bitLen) < len; ++bitLen);
	int *W = w + (1 << bitLen);
	W[0] = 1;
	W[1] = mod_pow(gen, (mod - 1) >> bitLen);
	for(int i = 2; i < (1 << bitLen); ++i)
		W[i] = (LL)W[i - 1] * W[1] % mod;
	for(int i = (1 << bitLen) - 1; i > 0; --i)
		w[i] = w[i << 1];
}
void NTT(int len, int x[], int flag) {
	register int i, j, k;
	for(i = 1, j = 0; i < len; ++i) {
		for(k = len >> 1; j >= k; j ^= k, k >>= 1);
		j < k && (j ^= k);
		if(i < j)
			std::swap(x[i], x[j]);
	}
	register int *W = w + 1, t;
	for(i = 1; i < len; i <<= 1)
		for(j = 0, W += i; j < len; j += i << 1)
			for(k = 0; k < i; ++k) {
				t = (LL)W[k] * x[i + j + k] % mod;
				x[i + j + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		for(j = 0, k = 1; (1 << j) < len; ++j, k = (LL)k * inv2 % mod);
		std::reverse(x + 1, x + len);
		for(i = 0; i < len; ++i)
			x[i] = (LL)x[i] * k % mod;
	}
}
int n, m, inv[maxs], f[maxs], g[maxs];
int main() {
	scanf("%d%d", &m, &n);
	initNTT(n << 1 | 1);
	inv[1] = g[0] = f[1] = 1;
	g[1] = mod - 1;
	for(int i = 2, ivs = 1; i <= n; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		ivs = (LL)ivs * inv[i] % mod;
		f[i] = (LL)mod_pow(i, n) * ivs % mod;
		g[i] = i & 1 ? mod - ivs : ivs;
	}
	int len;
	for(len = 1; len <= n + n; len <<= 1);
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	int ans = 0;
	for(int i = std::min(n, m - 1); i >= 0; --i)
		ans = ((LL)ans * (m - 1 - i) % mod * inv2 + f[i]) % mod;
	ans = (LL)ans * m % mod * mod_pow(2, m * (m - 1LL) / 2 % (mod - 1)) % mod;
	printf("%d\n", ans);
	return 0;
}
