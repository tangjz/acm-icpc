#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxLen = 22, maxm = 1 << maxLen, mod = 985661441, gen = 3; // maxn << 1 <= maxm
const int maxn = 2000000 + 1, maxk = 4, maxo = (maxn * 3 >> 1) + maxm + maxk;
int inv[maxn], fact[maxn];
inline int mod_inv(int x) {
	return x < maxn ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k; k >>= 1, x = (int)((LL)x * x % mod))
		ret = k & 1 ? (int)((LL)ret * x % mod) : ret;
	return ret;
}
int w[maxm | 1], inv2[maxLen + 1];
inline int mod_add(int x, int y) {
	return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
inline void NTT(int len, int x[], int flag) {
	static int hisLen = -1, bitLen, bitRev[maxm | 1];
	for(bitLen = 0; 1 << bitLen < len; ++bitLen);
	if(hisLen != bitLen) {
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
		hisLen = bitLen;
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			std::swap(x[i], x[bitRev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k) {
				int t = (LL)w[k << (maxLen - i)] * X[k + d] % mod;
				X[d + k] = mod_sub(X[k], t);
				X[k] = mod_add(X[k], t);
			}
	if(flag == -1) {
		std::reverse(x + 1, x + len);
		for(int i = 0, val = inv2[bitLen]; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
// poly exp
void PolyExp(int n, int cur[], int nxt[]) {
	// REQUIRE: cur[0 : n]
	// EFFECTS: NXT = e^CUR (mod x^len), len >= n, NXT[0 : len * 2] is used
	static int ivs[maxm | 1], tmp[maxm | 1];
	nxt[0] = ivs[0] = 1; // nxt * ivs = 1 (mod x^len)
	for(int len = 2; (len >> 1) < n; len <<= 1) {
		// before here, nxt = e^CUR (mod x^(len/2)), ivs = e^-CUR (mod x^(len/2))
		// nxt (mod x^(len/2)) -> nxt (mod x^(len/2)) * 4
		memset(nxt + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		// ivs (mod x^(len/2)) -> ivs (mod x^(len/2)) * 4
		memset(ivs + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		// tmp = NXT' (mod x^(len/2)) * 4
		for(int i = 1; i <= len >> 1; ++i)
			tmp[i - 1] = (LL)nxt[i] * i % mod;
		memset(tmp + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		// tmp = int(NXT'/NXT) = logNXT (mod x^len)
		NTT(len << 1, nxt, 1);
		NTT(len << 1, ivs, 1);
		NTT(len << 1, tmp, 1);
		for(int i = 0; i < len << 1; ++i)
			if((tmp[i] = (2 - (LL)nxt[i] * ivs[i]) % mod * ivs[i] % mod * tmp[i] % mod) < 0)
				tmp[i] += mod;
		NTT(len << 1, tmp, -1);
		for(int i = len - 1; i > 0; --i)
			tmp[i] = (LL)tmp[i - 1] * inv[i] % mod;
		tmp[0] = 0;
		// tmp = 1 - logNXT + CUR (mod x^len) * 2
		for(int i = 0; i < len; ++i) {
			if(tmp[i])
				tmp[i] = mod - tmp[i];
			if(i < n && (tmp[i] += cur[i]) >= mod)
				tmp[i] -= mod;
		}
		if(++tmp[0] >= mod)
			tmp[0] -= mod;
		memset(tmp + len, 0, len * sizeof(int));
		// nxt = NXT (1 - logNXT + CUR) (mod x^len)
		NTT(len << 1, tmp, 1);
		for(int i = 0; i < len << 1; ++i)
			nxt[i] = (LL)nxt[i] * tmp[i] % mod;
		NTT(len << 1, nxt, -1);
		// tmp = nxt (mod x^len) * 2
		memcpy(tmp, nxt, len * sizeof(int));
		memset(tmp + len, 0, len * sizeof(int));
		NTT(len << 1, tmp, 1);
		// ivs (mod x^(len/2)) * 4 -> ivs (mod x^len)
		for(int i = 0; i < len << 1; ++i)
			if((ivs[i] = (2 - (LL)tmp[i] * ivs[i]) % mod * ivs[i] % mod) < 0)
				ivs[i] += mod;
		NTT(len << 1, ivs, -1);
	}
}
int pool[maxo | 1], *f[maxk | 1], sz[maxk | 1];
int main() {
	// NTT init
	w[0] = 1; // make sure that mod = 2 ^ maxLen * k + 1
	w[1] = mod_pow(gen, (mod - 1) >> maxLen);
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxLen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	// poly init
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	f[1] = pool + 1;
	sz[1] = maxn;
	f[1][0] = 1;
	for(int i = 1; i < maxn; ++i)
		f[1][i] = (LL)f[1][i - 1] * inv[i] % mod;
	// poly NTT
	for(int i = 2; i < maxk; ++i)
	{
		f[i] = f[i - 1] + sz[i - 1] + 1;
		sz[i] = (maxn - 1) / i + 1;
		PolyExp(sz[i], f[i - 1] - 1, f[i]);
	}
	// poly output
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	for(int i = 1; i < maxk; ++i)
		for(int j = i; j < sz[i]; ++j)
			f[i][j] = (LL)f[i][j] * fact[j] % mod;
	int t, s, k;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &s, &k);
		printf("Case #%d: %d\n", Case, f[k < s ? k : s][s]);
	}
	return 0;
}
