#include <cstdio>
#include <algorithm>
const int maxn = 10000001;
int tot, prime[maxn], f[maxn];
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = -1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = -f[i];
			if(i % prime[j] == 0)
				break;
		}
		f[i] += f[i - 1];
	}
	int t, n, m;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n > m)
			std::swap(n, m);
		long long ans = (long long)n * m;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = std::min(n / (n / i), m / (m / i));
			ans -= (long long)(n / i) * (m / i) * (f[j] - f[i - 1]);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
