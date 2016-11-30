#include <cstdio>
const int maxn = 65536;
int tot, prime[maxn];
bool vis[maxn];
int phi(int x)
{
	int ret = x;
	for(int i = 0; i < tot && prime[i] <= x / prime[i]; ++i)
		if(x % prime[i] == 0)
		{
			ret -= ret / prime[i];
			while(x % prime[i] == 0)
				x /= prime[i];
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && prime[j] <= (maxn - 1) / i; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int n;
	while(scanf("%d", &n) == 1)
		printf("%d\n", phi(n) >> 1);
	return 0;
}
