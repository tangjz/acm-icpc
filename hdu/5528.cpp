#include <cstdio>
typedef unsigned long long ULL;
const int maxn = 32000;
int tot, prime[maxn], t, n;
bool vis[maxn];
ULL ans1, ans2;
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, o; j < tot && (o = i * prime[j]) < maxn; ++j)
		{
			vis[o] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		ans1 = ans2 = 1;
		for(int i = 0; i < tot && prime[i] * prime[i] <= n; ++i)
			if(n % prime[i] == 0)
			{
				int cnt = 0, tmp = 1;
				ULL sum = 1;
				for( ; n % prime[i] == 0; n /= prime[i], ++cnt);
				for(int j = 1; j <= cnt; ++j)
				{
					tmp *= prime[i];
					sum += (ULL)tmp * tmp;
				}
				ans1 *= sum;
				ans2 *= tmp * (cnt + 1ULL);
			}
		if(n > 1)
		{
			ans1 *= (ULL)n * n + 1;
			ans2 *= n * 2ULL;
		}
		printf("%llu\n", ans1 - ans2);
	}
	return 0;
}
