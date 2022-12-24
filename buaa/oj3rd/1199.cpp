#include <cstdio>
#include <cstring>
const int maxn = 5001; 
int t, n, tot, prime[maxn], fact[maxn], cnt[maxn];
int main()
{
	scanf("%d", &t);
	for(int i = 2; i < maxn; ++i)
	{
		if(!fact[i])
			fact[i] = prime[tot++] = i;
		for(int j = 0; j < tot && prime[j] <= (maxn - 1) / i; ++j)
		{
			fact[i * prime[j]] = fact[i];
			if(i % prime[j] == 0)
				break;
		}
	}
	while(scanf("%d", &n) == 1)
	{
		memset(cnt, 0, sizeof cnt);
		for(int i = 2; i <= n; ++i)
			cnt[i] = 1;
		for(int i = n; i > 1; --i)
			if(i != fact[i])
			{
				cnt[fact[i]] += cnt[i];
				cnt[i / fact[i]] += cnt[i];
			}
		bool flag = 0;
		for(int i = 0; i < tot && prime[i] <= n; ++i)
		{
			if(!cnt[prime[i]])
				continue;
			if(flag)
				putchar('*');
			else
				flag = 1;
			printf("%d", prime[i]);
			if(cnt[prime[i]] > 1)
				printf("^%d", cnt[prime[i]]);
		}
		putchar('\n');
	}
	return 0;
}
