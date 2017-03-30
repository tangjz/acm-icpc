#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 130001, maxlen = 18, maxm = 1 << maxlen, mod = 1004535809, gen = 3;
int w[maxm + 1], inv2[maxlen + 1];
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
	static int bitLen, bitrev[maxm + 1];
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
				int t = (LL)w[(maxm >> i) * k] * x[j + k + d] % mod;
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
void PolyInv(int n, int cur[], int nxt[maxm + 1])
{
	// EFFECTS: NXT = CUR^(-1), NXT[len/2 : len] is any number, len >= n * 2
	int len;
	static int tmp[maxm + 1];
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
int n, fact[maxn], iact[maxn], pw[maxn], f[maxm + 1], g[maxm + 1];
int main()
{
	w[0] = 1;
	w[1] = mod_pow(gen, (mod - 1) >> maxlen); // make sure that mod = 2 ^ maxlen * k + 1
	for(int i = 2; i < maxm; ++i)
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxlen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	scanf("%d", &n);
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = pw[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
		if((pw[i] = pw[i - 1] << 1) >= mod)
			pw[i] -= mod;
	}
	int len;
	for(len = 1; len <= n << 1; len <<= 1);
	f[0] = 1;
	for(int i = 1, v = 1; i <= n; ++i)
	{
		f[i] = (LL)v * iact[i] % mod;
		v = (LL)v * pw[i] % mod;
	}
	PolyInv(n + 1, f, g);
	f[0] = 0;
	for(int i = 1, v = 1; i <= n; ++i)
	{
		f[i] = (LL)v * iact[i - 1] % mod;
		v = (LL)v * pw[i] % mod;
	}
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	printf("%d\n", (int)((LL)f[n] * fact[n - 1] % mod));
	return 0;
}
