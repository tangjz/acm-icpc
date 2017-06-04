#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 1000001, mod = 1000000007;
int t, n, m, f[maxn], g[maxn];
inline int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	f[1] = f[2] = 1;
	for(int i = 3; i < maxn; ++i)
		if((f[i] = f[i - 1] + f[i - 2]) >= mod)
			f[i] -= mod;
	f[0] = g[0] = g[1] = g[2] = 1;
	for(int i = 3; i < maxn; ++i)
	{
		int val = mod_inv(f[i]);
		for(int j = i + i; j < maxn; j += i)
			f[j] = (LL)f[j] * val % mod;
		f[i] = (LL)f[i - 1] * f[i] % mod;
		g[i] = (LL)g[i - 1] * val % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		int ans = 1;
		scanf("%d%d", &n, &m);
		for(int i = 3, j, u, v; i <= n && i <= m; i = j + 1)
		{
			u = n / i;
			v = m / i;
			j = std::min(n / u, m / v);
			ans = (LL)ans * mod_pow((LL)f[j] * g[i - 1] % mod, (LL)u * v % (mod - 1)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
