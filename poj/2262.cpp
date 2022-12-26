#include <cstdio>
const int maxn = 1000001;
int tot, prime[maxn];
bool vis[maxn];
int main()
{
	vis[1] = 1;
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
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 0; i < tot && prime[i] <= n >> 1; ++i)
			if(!vis[n - prime[i]])
			{
				printf("%d = %d + %d\n", n, prime[i], n - prime[i]);
				break;
			}
	}
	return 0;
}
