#include <cstdio>
const int maxn = 10000001, maxs = 664579;
typedef long long LL;
int tot, prime[maxs], mu[maxn], f[maxn], t, n, m;
bool vis[maxn];
int main()
{
	mu[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
			f[i] = 1;
		}
		for(int j = 0; j < tot && (LL)i * prime[j] < maxn; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				f[i * prime[j]] = mu[i];
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				f[i * prime[j]] = mu[i] - f[i];
			}
		}
		f[i] += f[i - 1];
	}
	scanf("%d", &t);
	while(t--)
	{
		long long ans = 0;
		scanf("%d%d", &n, &m);
		if(n > m)
		{
			int t = n;
			n = m;
			m = t;
		}
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
			ans += (LL)(f[j] - f[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
