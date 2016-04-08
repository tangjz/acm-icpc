#include <cstdio>
const int maxn = 10000001;
int tot, prime[maxn], c[maxn], d[maxn], f[maxn];
int main()
{
	f[1] = -1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = i;
			c[i] = d[i] = f[i] = 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			if(i % prime[j] == 0)
			{
				c[o] = c[i] + 1;
				d[o] = d[i];
				f[o] = d[o] == 1 || c[d[o]] == c[o] ? -f[d[o]] : 0;
				break;
			}
			else
			{
				c[o] = 1;
				d[o] = i;
				f[o] = c[d[o]] == c[o] ? -f[d[o]] : 0;
			}
		}
	}
	f[1] = 0;
	for(int i = 2; i < maxn; ++i)
		f[i] += f[i - 1];
	int t, n, m;
	scanf("%d", &t);
	while(t--)
	{
		long long ans = 0;
		scanf("%d%d", &n, &m);
		if(n > m)
		{
			n = n + m;
			m = n - m;
			n = n - m;
		}
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
			ans += (long long)(f[j] - f[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
