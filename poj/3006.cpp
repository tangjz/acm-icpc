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
	int a, d, n, ans;
	while(scanf("%d%d%d", &a, &d, &n) == 3 && a + d + n)
	{
		for(ans = a; n; ans += d)
			if(!vis[ans])
				--n;
		printf("%d\n", ans -= d);
	}
	return 0;
}
