#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 2000001;
int tot, prime[maxn], phi[maxn], t, n, c[maxn];
LL f[maxn], ans;
int main()
{
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
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
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		memset(c + 1, 0, n * sizeof(int));
		for(int i = 1; i <= n; ++i)
			++c[phi[i]];
		for(int i = 1; i <= n; ++i)
			for(int j = i + i; j <= n; j += i)
				c[i] += c[j];
		ans = 0;
		for(int i = n; i >= 1; --i)
		{
			f[i] = (LL)c[i] * c[i];
			for(int j = i + i; j <= n; j += i)
				f[i] -= f[j];
			ans += f[i] * phi[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
