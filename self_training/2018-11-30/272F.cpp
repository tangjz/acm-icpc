#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)1e5 + 1, maxlen = 18, maxm = 1 << maxlen, mod = 998244353, gen = 3;
int w[maxm], inv2[maxlen + 1];
int t, n, fact[maxn], f[maxm];
inline int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
inline int mod_add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}
inline int mod_sub(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}
inline void NTT(int len, int x[], int flag) {
	static int bitLen, bitrev[maxm];
	for(bitLen = 0; 1 << bitLen < len; ++bitLen);
	for(int i = 1; i < len; ++i) {
	    bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
		if(i < bitrev[i])
			std::swap(x[i], x[bitrev[i]]);
	}
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0; k < d; ++k) {
				int t = (LL)w[(maxm >> i) * k] * x[j + k + d] % mod;
				x[j + d + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1) {
		std::reverse(x + 1, x + len);
		int val = inv2[bitLen];
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
void PolyInv(int n, int cur[], int nxt[maxm]) {
	int len;
	static int tmp[maxm];
	nxt[0] = 1;
	for(len = 2; (len >> 1) < n; len <<= 1) {
		int lim = std::min(n, len);
		memcpy(tmp, cur, lim * sizeof(int));
		memset(tmp + lim, 0, ((len << 1) - lim) * sizeof(int));
		NTT(len << 1, tmp, 1);
		memset(nxt + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		NTT(len << 1, nxt, 1);
		for(int i = 0; i < len << 1; ++i)
			if((nxt[i] = (2 - (LL)tmp[i] * nxt[i]) % mod * nxt[i] % mod) < 0)
				nxt[i] += mod;
		NTT(len << 1, nxt, -1);
	}
}
int main() {
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxlen);
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxlen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	PolyInv(maxn, fact, f);
	for(int i = 0; i < maxn; ++i)
		(f[i] = fact[i] + f[i]) >= mod && (f[i] -= mod);
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", f[n]);
	}
	return 0;
}
