#include <stdio.h>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int n, x, y, f[maxn], g[maxn], sf[maxn], sg[maxn], q, m, ans;
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
int main()
{
	scanf("%d%d%d", &n, &x, &y);
	f[0] = g[0] = sf[0] = sg[0] = 1;
	f[1] = (LL)x * mod_inv(y) % mod;
	g[1] = mod_inv(f[1]);
	sf[1] = mod_inv(f[1] - 1);
	sg[1] = mod_inv(g[1] - 1);
	for(int i = 2; i <= n; ++i)
	{
		f[i] = (LL)f[i - 1] * f[1] % mod;
		g[i] = (LL)g[i - 1] * g[1] % mod;
		sf[i] = sf[i - 1] * (LL)mod_inv(f[i] - 1) % mod;
		sg[i] = sg[i - 1] * (LL)mod_inv(g[i] - 1) % mod;
	}
	int invn = mod_inv(n);
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d", &m);
		if(!m)
		{
			printf("%d\n", invn);
			continue;
		}
		ans = 0;
		for(int i = 1; i <= m; ++i)
		{
			int tmp = (LL)(mod_pow(mod + 1 - f[i], m - 1) - mod_pow(mod + 1 - f[i], n - 1)) * mod_pow(g[i], m) % mod;
			if(tmp < 0)
				tmp += mod;
			if(i > 1)
				tmp = (LL)tmp * sg[i - 1] % mod;
			if(i < m)
				tmp = (LL)tmp * sf[m - i] % mod;
			if((ans += tmp) >= mod)
				ans -= mod;
		}
		ans = (LL)ans * mod_pow(f[1], (m * (m + 1LL) >> 1) % (mod - 1)) % mod * invn % mod;
		printf("%d\n", ans);
	}
	return 0;
}
