#include <cstdio>
const int maxn = 100001;
int tot, prime[maxn >> 3], f[maxn], t, n, p, q;
long long ans, delta;
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = f[i - 1];
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = f[i] + f[prime[j]];
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		delta = 1;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%d%d", &p, &q);
			ans += (long long)f[p] * q;
			if(p == 2)
				delta = 0;
		}
		printf("%lld\n", ans + delta);
	}
	return 0;
}
