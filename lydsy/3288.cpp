#include <cstdio>
const int maxn = 1000001, mod = 1000000007;
int n, tot, prime[maxn >> 3], phi[maxn], ans = 1;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0; j < tot && prime[j] <= n / i; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
		ans = (long long)ans * phi[i] % mod;
	}
	printf("%d\n", ans);
	return 0;
}
