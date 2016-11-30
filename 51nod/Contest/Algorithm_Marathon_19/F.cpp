#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxlen = 17, maxn = 1 << maxlen, mod1 = 23333, mod = 104857601, gen = 3;
int len, sei[maxn], A[maxn], B[maxn], M[maxn], C[maxn];
int w[maxn], inv2[maxlen + 1];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int mod_add(int x, int y)
{
	return x + y >= mod ? x + y - mod : x + y;
}
inline int mod_sub(int x, int y)
{
	return x - y < 0 ? x - y + mod : x - y;
}
inline void NTT(int len, int x[], int flag)
{
	static int bitLen, bitrev[maxn];
	for(bitLen = 0; 1 << bitLen < len; ++bitLen);
	for(int i = 1; i < len; ++i)
	{
	    bitrev[i] = (bitrev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
		if(i < bitrev[i])
			std::swap(x[i], x[bitrev[i]]);
	}
	for(int i = 1, d = 1; d < len; ++i, d <<= 1)
		for(int j = 0; j < len; j += d << 1)
			for(int k = 0; k < d; ++k)
			{
				int t = (LL)w[(maxn >> i) * k] * x[j + k + d] % mod;
				x[j + d + k] = mod_sub(x[j + k], t);
				x[j + k] = mod_add(x[j + k], t);
			}
	if(flag == -1)
	{
		std::reverse(x + 1, x + len);
		int val = inv2[bitLen];
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
void polyInv(int n, int cur[], int nxt[maxn])
{
	// EFFECTS: NXT = CUR^(-1), NXT[len/2 : len] is any number, len >= n * 2
	int len;
	static int tmp[maxn];
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
void polyDiv(int n, int a[], int m, int b[], int d[], int r[])
{
	if(n < m)
	{
		d[0] = 0;
		memcpy(r, a, n * sizeof(int));
		return;
	}
	int len = 1, plen = n - m + 1;
	static int x[maxn], y[maxn];
	for( ; len < plen << 1; len <<= 1);
	memcpy(x, b, m * sizeof(int));
	std::reverse(x, x + m);
	if(m < len)
		memset(x + m, 0, (len - m) * sizeof(int));
	polyInv(plen, x, y);
	memset(y + plen, 0, (len - plen) * sizeof(int));
	NTT(len, y, 1);
	memcpy(x, a, n * sizeof(int));
	std::reverse(x, x + n);
	memset(x + plen, 0, (len - plen) * sizeof(int));
	NTT(len, x, 1);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, -1);
	std::reverse(x, x + plen);
	memcpy(d, x, plen * sizeof(int));
	for(len = 1; len < n; len <<= 1);
	memset(x + plen, 0, (len - plen) * sizeof(int));
	NTT(len, x, 1);
	memcpy(y, b, m * sizeof(int));
	memset(y + m, 0, (len - m) * sizeof(int));
	NTT(len, y, 1);
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * y[i] % mod;
	NTT(len, x, -1);
	for(int i = 0; i < m; ++i)
		r[i] = mod_sub(a[i], x[i]);
}
inline void poly_mul(int aLen, int *A, int bLen, int *B, int &cLen, int *C) // C = A * B
{
	int len;
	static int x[maxn], y[maxn];
	for(len = 1; len < aLen + bLen - 1; len <<= 1);
	if(A != B)
	{
		memcpy(x, A, aLen * sizeof(int));
		memset(x + aLen, 0, (len - aLen) * sizeof(int));
		memcpy(y, B, bLen * sizeof(int));
		memset(y + bLen, 0, (len - bLen) * sizeof(int));
		NTT(len, x, 1);
		NTT(len, y, 1);
		for(int i = 0; i < len; ++i)
			C[i] = (LL)x[i] * y[i] % mod;
	}
	else
	{
		memcpy(x, A, aLen * sizeof(int));
		memset(x + aLen, 0, (len - aLen) * sizeof(int));
		NTT(len, x, 1);
		for(int i = 0; i < len; ++i)
			C[i] = (LL)x[i] * x[i] % mod;
	}
	NTT(len, C, -1);
	for(cLen = aLen + bLen - 1; cLen && !C[cLen - 1]; --cLen);
}
inline void poly_mod(int aLen, int *A, int bLen, int *B, int &cLen, int *C) // C = A % B
{
	static int D[maxn];
	polyDiv(aLen, A, bLen, B, D, C);
	for(cLen = bLen; cLen && !C[cLen - 1]; --cLen);
}
int main()
{
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxlen); // make sure that mod = 2 ^ maxlen * k + 1
	for(int i = 2; i < maxn; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxlen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	LL m;
	int mx = 2;
	{
		int n, x, a, b;
		scanf("%d%lld%d%d%d", &n, &m, &x, &a, &b);
		for(int i = 1; i <= n; ++i, x = ((LL)x * a + b) % mod1 + 1)
		{
			if(x > mod1)
				continue;
			++sei[x];
			if(mx < x)
				mx = x;
		}
	}
	M[mx] = 1;
	for(int i = 0; i < mx; ++i)
		M[i] = sei[mx - i] ? mod - sei[mx - i] : 0;
	int aLen = 1, bLen = 2, mLen = mx + 1;
	A[0] = 1;
	B[1] = 1;
	for(m += mx - 1; m > 0; )
	{
		int cLen;
		if(m & 1)
		{
			poly_mul(aLen, A, bLen, B, cLen, C);
			poly_mod(cLen, C, mLen, M, aLen, A);
		}
		if(m >>= 1)
		{
			poly_mul(bLen, B, bLen, B, cLen, C);
			poly_mod(cLen, C, mLen, M, bLen, B);
		}
	}
	printf("%d\n", aLen == mx ? A[mx - 1] : 0);
	return 0;
}
