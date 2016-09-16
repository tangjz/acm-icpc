#include <cstdio>
typedef long long LL;
const int maxn = 1000001;
int tot, prime[maxn], t, ans;
bool vis[maxn];
LL n;
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i * prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		ans = n & 1 ? 2 : 6;
		for( ; !(n & 1); n >>= 1);
		for(int i = 1; i < tot && (LL)prime[i] * prime[i] <= n; ++i)
			if(n % prime[i] == 0)
			{
				int c = 0;
				for(n /= prime[i], ++c; n % prime[i] == 0; n /= prime[i], ++c);
				if(prime[i] % 6 == 1)
					ans *= c << 1 | 1;
			}
		if(n > 1 && n % 6 == 1)
			ans *= 3;
		printf("%d\n", ans);
	}
	return 0;
}
