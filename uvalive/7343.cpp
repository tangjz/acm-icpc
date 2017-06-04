#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxlen = 17, maxm = 1 << maxlen, mod = 7340033, gen = 3;
int fact[maxn], iact[maxn], w[maxm], inv2[maxlen + 1];
int cnt[2][2], sz[2], f[2][maxm];
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
	return x + y >= mod ? x + y - mod : x + y;
}
inline int mod_sub(int x, int y)
{
	return x - y < 0 ? x - y + mod : x - y;
}
inline void NTT(int len, int x[], int flag)
{
	for(int i = 0, j = 0; i < len; ++i)
	{
		if(i > j)
			std::swap(x[i], x[j]);
		for(int l = len >> 1; (j ^= l) < l; l >>= 1);
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
		int bitLen = 0;
		for( ; 1 << bitLen < len; ++bitLen);
		int val = inv2[bitLen];
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * val % mod;
	}
}
inline int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
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
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		int n;
		scanf("%d", &n);
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < n; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			++cnt[x < 0][y < 0];
		}
		for(int i = 0; i < 2; ++i)
			sz[i] = min(cnt[0][i], cnt[1][i ^ 1]);
		int len;
		for(len = 1; len <= sz[0] + sz[1]; len <<= 1);
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < len; ++j)
				f[i][j] = j <= sz[i] ? (LL)C(cnt[0][i], j) * C(cnt[1][i ^ 1], j) % mod : 0;
		NTT(len, f[0], 1);
		NTT(len, f[1], 1);
		for(int i = 0; i < len; ++i)
			f[0][i] = (LL)f[0][i] * f[1][i] % mod;
		NTT(len, f[0], -1);
		printf("Case %d:\n", Case);
		for(int i = 1; i <= n; ++i)
			printf("%d%c", (i & 1) || (i >> 1) >= len ? 0 : f[0][i >> 1], " \n"[i == n]);
	}
	return 0;
}
