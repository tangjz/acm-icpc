#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxLen = 18, maxm = 1 << maxLen, mod = 998244353, gen = 3;
int w[maxm | 1], inv2[maxLen + 1];
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
inline int mod_add(int x, int y)
{
	return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y)
{
	return (x -= y) < 0 ? x + mod : x;
}
inline void NTT(int len, int x[], int flag)
{
	static int hisLen = -1, bitLen, bitRev[maxm];
	for(bitLen = 0; 1 << bitLen < len; ++bitLen);
	if(hisLen != bitLen)
	{
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
		hisLen = bitLen;
	}
	for(int i = 1; i < len; ++i)
		if(i < bitRev[i])
			std::swap(x[i], x[bitRev[i]]);
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0, *X = x + j; k < d; ++k)
			{
				int t = (LL)w[k << (maxLen - i)] * X[k + d] % mod;
				X[d + k] = mod_sub(X[k], t);
				X[k] = mod_add(X[k], t);
			}
	if(flag == -1)
	{
		std::reverse(x + 1, x + len);
		int val = inv2[bitLen];
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
void PolyInv(int n, int cur[], int nxt[maxm])
{
	// EFFECTS: NXT = CUR^(-1), NXT[len/2 : len] is any number, len >= n * 2
	int len;
	static int tmp[maxm];
	// nxt = CUR^(-1) (mod x)
	nxt[0] = 1; //mod_inv(cur[0]);
	for(len = 2; (len >> 1) < n; len <<= 1)
	{
		// before here, nxt = CUR^(-1) (mod x^(len/2)), nxt[len/2 : len] is any number
		int lim = std::min(n, len);
		// tmp = CUR (mod x^min(n,len)) -> tmp (mod x^(len*2))
		memcpy(tmp, cur, lim * sizeof(int));
		memset(tmp + lim, 0, ((len << 1) - lim) * sizeof(int));
		NTT(len << 1, tmp, 1);
		// nxt (mod x^(len/2)) -> nxt (mod x^(len*2))
		memset(nxt + (len >> 1), 0, ((len << 1) - (len >> 1)) * sizeof(int));
		NTT(len << 1, nxt, 1);
		// nxt = (2 - CUR * nxt) * nxt (mod x^len), nxt[len : len * 2] is any number
		for(int i = 0; i < len << 1; ++i)
			if((nxt[i] = (2 - (LL)tmp[i] * nxt[i]) % mod * nxt[i] % mod) < 0)
				nxt[i] += mod;
		NTT(len << 1, nxt, -1);
	}
}
int n, m, inv[maxn], A[maxm | 1], B[maxm | 1], C[maxm | 1], D[maxm | 1];
void cdq(int L, int R) // 2 A' = B A
{
	if(L == R)
	{
		A[L] = L ? (LL)A[L] * inv[L] % mod : 1;
		return;
	}
	int M = (L + R) >> 1;
	cdq(L, M);
	int len, plen = R - L, qlen = M - L + 1;
	for(len = 1; len < plen; len <<= 1);
	memcpy(C, A + L, qlen * sizeof(int));
	memset(C + qlen, 0, (len - qlen) * sizeof(int));
	NTT(len, C, 1);
	memcpy(D, B, plen * sizeof(int));
	memset(D + plen, 0, (len - plen) * sizeof(int));
	NTT(len, D, 1);
	for(int i = 0; i < len; ++i)
		C[i] = (LL)C[i] * D[i] % mod;
	NTT(len, C, -1);
	for(int i = M + 1, *_C = C - L - 1; i <= R; ++i)
		if((A[i] += _C[i]) >= mod)
			A[i] -= mod;
	cdq(M + 1, R);
}
int main()
{
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxLen); // make sure that mod = 2 ^ maxLen * k + 1
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxLen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	scanf("%d%d", &m, &n);
	++n;
	while(m--)
	{
		int x;
		scanf("%d", &x);
		if(x < n)
			++A[x];
	}
	A[0] = 1;
	for(int i = 1; i < n; ++i)
		if(A[i])
			A[i] = mod - (A[i] << 2);
	inv[1] = 1;
	for(int i = 2; i < n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	int len;
	for(len = 1; len < n << 1; len <<= 1);
	memset(A + n, 0, (len - n) * sizeof(int));
	PolyInv(n, A, B);
	memset(B + n, 0, (len - n) * sizeof(int));
	NTT(len, B, 1);
	for(int i = 1; i < n; ++i)
		A[i - 1] = (LL)A[i] * i % mod;
	A[n - 1] = 0;
	NTT(len, A, 1);
	for(int i = 0; i < len; ++i)
		B[i] = (LL)A[i] * B[i] % mod;
	NTT(len, B, -1);
	for(int i = 0; i < n; ++i)
		B[i] = (LL)B[i] * inv2[1] % mod;
	memset(A, 0, len * sizeof(int));
	cdq(0, n - 1);
	for(int i = 1; i < n; ++i)
		A[i] = (LL)A[i] * inv2[1] % mod;
	PolyInv(n, A, B);
	for(int i = 1; i < n; ++i)
		printf("%d\n", B[i]);
	return 0;
}
