#include <cstdio>
const int maxn = 151;
int tot, prime[maxn], f[maxn], c[maxn], n, x, cnt;
long long ans;
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
	{
		if(!f[i])
			prime[tot++] = f[i] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) <= n; ++j)
		{
			f[o] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
	if(n == 1)
	{
		scanf("%d", &x);
		printf("%d\n", !x ? 1 : 0);
		return 0;
	}
	ans = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		if(!x)
		{
			puts("0");
			return 0;
		}
		--c[x - 1];
		cnt += x - 1;
	}
	if(cnt != n - 2)
	{
		puts("0");
		return 0;
	}
	++c[n - 2];
	for(int i = n; i >= 1; --i)
		c[i] += c[i + 1];
	for(int i = n; i >= 2; --i)
		if(i != f[i])
		{
			c[f[i]] += c[i];
			c[i / f[i]] += c[i];
		}
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < c[prime[i]]; ++j)
			ans *= prime[i];
	printf("%lld\n", ans);
	return 0;
}
