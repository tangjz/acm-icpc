#include <cstdio>
typedef long long LL;
const int maxn = 1000001;
const LL mod = 1000000000000000000LL;
int tot, prime[maxn], phi[maxn];
LL f[maxn], g[maxn];
int main()
{
	phi[1] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		if(!phi[i])
		{
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j])
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			else
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
	}
	for(int i = 1; i < maxn; ++i)
	{
		for(int j = i + i, k = 2; j < maxn; j += i, ++k)
		{
			f[j] += (LL)j * k * phi[k];
			if(f[j] >= mod)
			{
				g[j] += f[j] / mod;
				f[j] %= mod;
			}
		}
		f[i] += f[i - 1] + i;
		g[i] += g[i - 1];
		while(f[i] >= mod)
		{
			++g[i];
			f[i] -= mod;
		}
	}
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		if(!g[n])
			printf("%lld\n", f[n]);
		else
			printf("%lld%018lld\n", g[n], f[n]);
	}
	return 0;
}
