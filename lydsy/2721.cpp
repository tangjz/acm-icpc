#include <cstdio>
const int maxn = 1000001, mod = 1000000007;
int n, tot, prime[maxn], f[maxn], cnt[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = i;
		}
		for(int j = 0, k = n / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = f[i];
			if(i % prime[j] == 0)
				break;
		}
		++cnt[i];
	}
	for(int i = n; i >= 2; --i)
		if(i != f[i])
		{
			cnt[f[i]] += cnt[i];
			cnt[i / f[i]] += cnt[i];
		}
	int ans = 1;
	for(int i = 0; i < tot && prime[i] <= n; ++i)
		ans = ans * (cnt[prime[i]] * 2LL + 1) % mod;
	printf("%d\n", ans);
	return 0;
}
