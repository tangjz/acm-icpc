#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 1 << 15 | 1, maxLen = 16, maxm = 1 << maxLen, mod = 998244353, gen = 3;
int inv[maxn];
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
int n, m, len;
struct Matrix {
	int f[maxn], g[maxn];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		static int A[maxm | 1], B[maxm | 1], C[maxm | 1], D[maxm | 1], E[maxm | 1], F[maxm | 1];
		A[0] = 0;
		memcpy(A + 1, f, (m - 1) * sizeof(int));
		memset(A + m, 0, (len - m) * sizeof(int));
		memcpy(B, g, m * sizeof(int));
		memset(B + m, 0, (len - m) * sizeof(int));
		memcpy(C, t.f, m * sizeof(int));
		memset(C + m, 0, (len - m) * sizeof(int));
		memcpy(D, t.g, m * sizeof(int));
		memset(D + m, 0, (len - m) * sizeof(int));
		memcpy(E, D, len * sizeof(int));
		for(int i = 1; i < m; ++i) {
			if((E[i] += C[i - 1]) >= mod)
				E[i] -= mod;
			if((E[i] += D[i - 1]) >= mod)
				E[i] -= mod;
		}
		NTT(len, A, 1);
		NTT(len, B, 1);
		NTT(len, C, 1);
		NTT(len, D, 1);
		NTT(len, E, 1);
		for(int i = 0; i < len; ++i)
			F[i] = ((LL)A[i] * C[i] + (LL)B[i] * D[i]) % mod;
		NTT(len, F, -1);
		memcpy(ret.f, F, m * sizeof(int));
		for(int i = 0; i < len; ++i)
			F[i] = ((LL)A[i] * D[i] + (LL)B[i] * E[i]) % mod;
		NTT(len, F, -1);
		memcpy(ret.g, F, m * sizeof(int));
		return ret;
	}
	Matrix pow(int k) {
		Matrix ret = *this, tmp = *this;
		--k;
		for( ; k; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
} G;
int main() {
	w[0] = 1; // make sure that mod = 2 ^ maxLen * k + 1
	w[1] = mod_pow(gen, (mod - 1) >> maxLen);
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxLen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	scanf("%d%d", &n, &m);
	++n, ++m;
	for(len = 1; len < m << 1; len <<= 1);
	G.g[0] = 1;
	G = G.pow(n);
	--m;
	for(int i = 1; i <= m; ++i)
		printf("%d%c", G.g[i], " \n"[i == m]);
	return 0;
}
