#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 100001, maxk = 11, mod = 1000003;
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
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int fact[maxn], inv[maxn], f[maxk][maxn], g[maxn];
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		f[0][i] = g[i] = 1;
		fact[i] = fact[i - 1];
		for(int j = 0; j < 10; ++j)
			fact[i] = (LL)fact[i] * i % mod;
	}
	for(int i = 1; i < maxk; ++i)
	{
		memcpy(f[i], f[i - 1], sizeof f[0]);
		for(int j = 2; j < maxn; ++j)
		{
			g[j] = g[j] * (1LL + inv[j - 1]) % mod;
			f[i][j] = (f[i][j] + (LL)g[j] * f[i][j - 1]) % mod;
		}
	}
	for(int n, k, ans; scanf("%d%d", &n, &k) == 2 && !(!n && !k); )
	{
		ans = (LL)f[k + 1][n] * fact[n] % mod;
		printf("%d\n", ans);
	}
	return 0;
}
