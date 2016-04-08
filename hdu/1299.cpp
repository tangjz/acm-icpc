#include <cstdio>
const int maxp = 31608;
int tot, prime[maxp], t, n, ans;
bool vis[maxp];
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxp - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		ans = 1;
		for(int i = 0; i < tot && prime[i] <= n / prime[i]; ++i)
			if(n % prime[i] == 0)
			{
				int cnt = 0;
				for( ; n % prime[i] == 0; n /= prime[i])
					++cnt;
				ans = ans * (cnt * 2 + 1);
			}
		if(n > 1)
			ans = ans * 3;
		printf("Scenario #%d:\n%d\n\n", Case, ans + 1 >> 1);
	}
	return 0;
}
