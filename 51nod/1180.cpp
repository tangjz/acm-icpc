#include <cstdio>
typedef long long LL;
const int maxn = 5000001;
int tot, prime[maxn / 12], mu[maxn], n, m;
LL ans;
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	--n;
	--m;
	if(n > m)
	{
		n = n + m;
		m = n - m;
		n = n - m;
	}
	ans = (n > 0) + (m > 0) + (LL)n * m;
	for(int i = 2; i <= n; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0, k = n / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j])
				mu[i * prime[j]] = -mu[i];
			else
				break;
		}
		if(mu[i])
			ans += mu[i] * (n / i) * (LL)(m / i);
	}
	printf("%lld\n", ans);
	return 0;
}
