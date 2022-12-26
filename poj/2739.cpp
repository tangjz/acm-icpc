#include <cstdio>
const int maxn = 10001;
int tot, prime[maxn], n, ans, sum;
bool vis[maxn];
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
	while(scanf("%d", &n) == 1 && n)
	{
		ans = sum = 0;
		for(int i = 0, j = 0; i < tot && prime[i] <= n; ++i)
		{
			sum += prime[i];
			while(j < i && sum > n)
				sum -= prime[j++];
			if(sum == n)
				++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
