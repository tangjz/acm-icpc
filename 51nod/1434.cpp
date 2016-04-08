#include <cstdio>
const int maxn = 1000001;
int tot, prime[maxn], t, n, m;
bool vis[maxn];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		m = n + 1;
		for(int i = 0; i < tot && prime[i] <= n; ++i)
		{
			int tmp;
			for(tmp = prime[i]; tmp <= n / prime[i]; tmp *= prime[i]);
			tmp = (n / tmp + 1) * tmp;
			if(m < tmp)
				m = tmp;
		}
		printf("%d\n", m);
	}
	return 0;
}
