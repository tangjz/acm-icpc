#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 1000000009, inv2 = mod + 1 >> 1;
int tot, prime[maxn >> 3];
int d[maxn], c[maxn], f[maxn], res;
LL lastn;
int s(LL n)
{
	if(lastn == n)
		return res;
	lastn = n;
	if(n < maxn)
		return res = c[n];
	res = 0;
	for(LL i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		res = (res + n / i % mod * (j - i + 1) % mod * ((i + j) % mod)) % mod;
	}
	res = (LL)res * inv2 % mod;
	return res;
}
int main()
{
	f[1] = c[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!c[i])
		{
			prime[tot++] = i;
			d[i] = 1;
			c[i] = i + 1;
			f[i] = -i;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			if(i % prime[j])
			{
				d[o] = i;
				c[o] = c[i] * (prime[j] + 1);
				f[o] = f[i] * -prime[j];
			}
			else
			{
				d[o] = d[i];
				c[o] = c[i] * prime[j] + c[d[o]];
				f[o] = 0;
				break;
			}
		}
	}
	for(int i = 1; i < maxn; ++i)
	{
		c[i] += c[i - 1];
		if(c[i] >= mod)
			c[i] -= mod;
	}
	for(LL n; scanf("%lld", &n) == 1; )
	{
		int ans = 0, lim = (int)ceil(sqrt(n));
		for(int i = 1; i <= lim; ++i)
			if(f[i])
				ans = (ans + (LL)f[i] * s(n / i / i)) % mod;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
