#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxLen = 15, maxm = 1 << maxLen | 1, mod = 998244353, gen = 3;
int w[maxm], inv2[maxLen + 2];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
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
void NTT(int len, int x[], int flag)
{
	static int bitLen = 0, ivs = 1, bitRev[maxm] = {};
	if(len != (1 << bitLen))
	{
		for(bitLen = 0; 1 << bitLen < len; ++bitLen);
		ivs = inv2[bitLen];
		for(int i = 1; i < len; ++i)
		    bitRev[i] = (bitRev[i >> 1] >> 1) | ((i & 1) << (bitLen - 1));
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
	for(int i = 0; i < len; ++i)
		x[i] = (LL)x[i] * ivs % mod;
}
const int maxq = 101, maxn = 10001, maxk = 21;
int inv[maxn], pw[maxn], s[maxk][maxk], f[maxk][maxn], g[maxm], h[maxm];
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
	inv[1] = pw[0] = pw[1] = f[0][0] = f[1][1] = 1;
	for(int i = 2, pw2 = 1, ivs = 1; i < maxn; ++i)
	{
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		pw2 = mod_add(pw2, pw2);
		pw[i] = (LL)pw[i - 1] * pw2 % mod * inv[i] % mod;
		ivs = (LL)ivs * inv[i] % mod;
		f[1][i] = (LL)mod_pow(i, i - 2) * ivs % mod;
	}
	s[0][0] = 1;
	for(int i = 1; i < maxk; ++i)
	{
		for(int j = 1; j < i; ++j)
			s[i][j] = (s[i - 1][j - 1] + (LL)j * s[i - 1][j]) % mod;
		s[i][i] = 1;
	}
	int len;
	for(len = 1; len < maxn << 1; len <<= 1);
	memcpy(g, f[1], maxn * sizeof(int));
	NTT(len, g, 1);
	memcpy(h, g, len * sizeof(int));
	for(int i = 2; i < maxk; ++i)
	{
		for(int j = 0; j < len; ++j)
			h[j] = (LL)g[j] * h[j] % mod;
		NTT(len, h, -1);
		memcpy(f[i], h, maxn * sizeof(int));
		if(i == maxk - 1)
			continue;
		memset(h + maxn, 0, (len - maxn) * sizeof(int));
		NTT(len, h, 1);
	}
	int t, n, k;
	scanf("%d", &t);
	while(t--)
	{
		int ans = 0;
		scanf("%d%d", &n, &k);
		for(int i = 0; i <= k; ++i)
		{
			if(!s[k][i])
				continue;
			int tmp = 0;
			for(int j = i; j <= n; ++j)
				tmp = (tmp + (LL)pw[n - j] * f[i][j]) % mod;
			ans = (ans + (LL)tmp * s[k][i]) % mod;
		}
		for(int i = 2; i <= n; ++i)
			ans = (LL)ans * i % mod;
		printf("%d\n", ans);
	}
	return 0;
}
