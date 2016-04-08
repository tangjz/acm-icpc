#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxm = 50002, mod = 1000000007;
int t, m, iact[maxm], tot, prime[maxm], f[maxm], pre[maxm], suf[maxm], ans;
long long n;
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	iact[1] = 1;
	for(int i = 2; i < maxm; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	while(t--)
	{
		scanf("%lld%d", &n, &m);
		++m;
		tot = 0;
		memset(f, 0, (m + 1) * sizeof(int));
		f[1] = 1;
		for(int i = 2; i <= m; ++i)
		{
			if(!f[i])
			{
				prime[tot++] = i;
				f[i] = mod_pow(i, m - 1);
			}
			for(int j = 0, k = m / i; j < tot && prime[j] <= k; ++j)
			{
				f[i * prime[j]] = (LL)f[i] * f[prime[j]] % mod;
				if(i % prime[j] == 0)
					break;
			}
		}
		for(int i = 2; i <= m; ++i)
		{
			f[i] += f[i - 1];
			if(f[i] >= mod)
				f[i] -= mod;
		}
		if(n <= m)
		{
			printf("%d\n", f[(int)n]);
			continue;
		}
		pre[0] = n % mod;
		for(int i = 1; i <= m; ++i)
			pre[i] = (n - i) % mod * pre[i - 1] % mod;
		suf[m] = (n - m) % mod;
		for(int i = m - 1; i >= 0; --i)
			suf[i] = (n - i) % mod * suf[i + 1] % mod;
		ans = 0;
		for(int i = 0; i <= m; ++i)
		{
			int tmp = (LL)f[i] * iact[i] % mod * iact[m - i] % mod;
			if(i)
				tmp = (LL)tmp * pre[i - 1] % mod;
			if(i < m)
				tmp = (LL)tmp * suf[i + 1] % mod;
			if(((m - i) & 1) && tmp)
				tmp = mod - tmp;
			ans += tmp;
			if(ans >= mod)
				ans -= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
