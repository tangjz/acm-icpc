#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxm = 1010, mod = 1000000007;
int t, m, tot, prime[maxm], f[maxm], iact[maxm], pre[maxm], suf[maxm], ans;
long long n;
int inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)inv(mod % x) % mod;
}
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
	while(t--)
	{
		scanf("%lld%d", &n, &m);
		++m;
		memset(f, 0, (m + 1) * sizeof(int));
		f[1] = 1;
		tot = 0;
		for(int i = 2; i <= m; ++i)
		{
			if(!f[i])
			{
				prime[tot++] = i;
				f[i] = mod_pow(i, m - 1);
			}
			for(int j = 0; j < tot && prime[j] <= m / i; ++j)
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
		iact[1] = 1;
		for(int i = 2; i <= m; ++i)
			iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
		iact[0] = 1;
		for(int i = 1; i <= m; ++i)
			iact[i] = (LL)iact[i - 1] * iact[i] % mod;
		pre[0] = n % mod;
		for(int i = 1; i <= m; ++i)
			pre[i] = (LL)pre[i - 1] * ((n - i) % mod) % mod;
		suf[m] = (n - m) % mod;
		for(int i = m - 1; i >= 0; --i)
			suf[i] = (LL)suf[i + 1] * ((n - i) % mod) % mod;
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
