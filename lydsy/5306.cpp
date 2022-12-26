#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e7 + 1, maxLen = 18, maxs = 1 << maxLen | 1, mod = 1004535809, gen = 3, inv2 = (mod + 1) >> 1;
int n, m, dt, ifct[maxn], w[maxs << 1 | 1], f[maxs], g[maxs];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : (x - mod);
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
	static int bitLen = 0, ivs = 1, bitRev[maxs] = {};
	if(len != (1 << bitLen)) {
		for(bitLen = 0, ivs = 1; (1 << bitLen) < len; ++bitLen, ivs = (LL)ivs * inv2 % mod);
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			swap(x[i], x[bitRev[i]]);
	for(int d = 1; d < len; d <<= 1)
		for(int j = 0, *W = w + (d << 1); j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k) {
				int t = (LL)W[k] * X[k + d] % mod;
				X[d + k] = mod_add(X[k], mod - t);
				X[k] = mod_add(X[k], t);
			}
	if(flag == -1) {
		reverse(x + 1, x + len);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * ivs % mod;
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &dt);
	int upp = max(n, m);
	ifct[0] = ifct[1] = 1;
	for(int i = 2; i <= upp; ++i)
		ifct[i] = mod - (int)(mod / i * (LL)ifct[mod % i] % mod);
	for(int i = 2; i <= upp; ++i)
		ifct[i] = (LL)ifct[i - 1] * ifct[i] % mod;
	upp = m;
	if(dt > 0)
		upp = min(upp, n / dt);
	for(int i = 0; i <= upp; ++i) {
		scanf("%d", f + i);
		f[i] = (LL)f[i] * ifct[i] % mod;
		g[i] = i & 1 ? mod - ifct[i] : ifct[i];
	}
	int len;
	for(len = 1; len < (upp << 1 | 1); len <<= 1);
	initNTT(len);
	memset(f + upp + 1, 0, (len - upp - 1) * sizeof(int));
	memset(g + upp + 1, 0, (len - upp - 1) * sizeof(int));
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	int ans = 0, prd = 1;
	for(int i = 0; i <= upp; ++i, prd = (LL)prd * ifct[dt] % mod)
		ans = (ans + (LL)mod_pow(m - i, n - i * dt) * ifct[m - i] % mod * ifct[n - i * dt] % mod * prd % mod * f[i]) % mod;
	for(int i = 2; i <= n; ++i)
		ans = (LL)ans * i % mod;
	for(int i = 2; i <= m; ++i)
		ans = (LL)ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
