#include <cstdio>
#include <cstring>
const int maxn = 100010, mod = 1000000007;
int t, n, tot, prime[maxn], fact[maxn], cnt[maxn], ans;
bool vis[maxn];
int mod_pow(int x, unsigned int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (long long)ret * x % mod;
		x = (long long)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
		if(!vis[i])
		{
			prime[tot++] = i;
			for(int j = i; j < maxn; j += i)
			{
				vis[j] = 1;
				fact[j] = i;
			}
		}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = 1;
		scanf("%d", &n);
		memset(cnt, 0, sizeof cnt);
		for(int i = 2; i <= n; ++i)
			cnt[i] = 1;
		for(int i = n; i >= 2; --i)
			if(fact[i] != i)
			{
				cnt[fact[i]] += cnt[i];
				cnt[i / fact[i]] += cnt[i];
			}
		--cnt[2];
		for(int i = 0; i < tot; ++i)
		{
			int &x = prime[i], &p = cnt[prime[i]];
			if(!p)
				continue;
			ans = (long long)ans * mod_pow(x, p - 1) % mod * ((long long)(x - 1) * p % mod + x) % mod;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
