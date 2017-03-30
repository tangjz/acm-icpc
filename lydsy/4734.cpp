#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 20001, maxLen = 16, maxm = 1 << maxLen | 1, mod = 998244353, gen = 3;
int w[maxm], inv2[maxLen + 1];
inline int mod_add(int x, int y)
{
	return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y)
{
	return (x -= y) < 0 ? x + mod : x;
}
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
void NTT(int len, int x[], int flag)
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
				int t = (LL)w[k << (maxLen - i)] * X[k + d] % mod; // avoid maxm
				X[d + k] = mod_sub(X[k], t);
				X[k] = mod_add(X[k], t);
			}
	if(flag != -1)
		return;
	std::reverse(x + 1, x + len);
	for(int i = 0, ivs = inv2[bitLen]; i < len; ++i)
		x[i] = (LL)x[i] * ivs % mod;
}
int n, m, v, len, inv[maxn], f[maxm], g[maxm], ans;
int main()
{
	w[0] = 1; // make sure that mod = 2 ^ maxLen * k + 1
	w[1] = mod_pow(gen, (mod - 1) >> maxLen); // avoid maxm
	for(int i = 2; i < maxm; ++i) // w[1 << maxLen] = 1
		w[i] = (LL)w[i - 1] * w[1] % mod;
	inv2[0] = 1;
	inv2[1] = (mod + 1) >> 1;
	for(int i = 2; i <= maxLen; ++i)
		inv2[i] = (LL)inv2[i - 1] * inv2[1] % mod;
	scanf("%d%d%d", &m, &n, &v);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 0, ivs = 1; i <= n; ivs = (LL)ivs * inv[++i] % mod)
	{
		scanf("%d", f + i);
		f[i] = (LL)f[i] * ivs % mod;
		g[i] = i & 1 ? mod - ivs : ivs;
	}
	for(len = 1; len <= n << 1; len <<= 1);
	NTT(len, f, 1);
	NTT(len, g, 1);
	for(int i = 0; i < len; ++i)
		f[i] = (LL)f[i] * g[i] % mod;
	NTT(len, f, -1);
	for(int i = 0, val = 1; i <= n; val = (LL)val * (m - (i++)) % mod * v % mod)
		ans = (ans + (LL)f[i] * val) % mod;
	printf("%d\n", ans);
	return 0;
}
