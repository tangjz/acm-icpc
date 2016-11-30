#include <stdio.h>
typedef long long LL;
const int maxn = 100000001, mod = 1000000009;
int tot, prime[maxn >> 3], d[maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
			prime[tot++] = d[i] = i;
		for(int j = 0, k = (maxn - 1) / i, o; prime[j] <= k; ++j)
		{
			d[o = i * prime[j]] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	for(int n; scanf("%d", &n) == 1; )
	{
		int ans = 1;
		for(int i = 0; i < tot && prime[i] <= n; ++i)
		{
			int tmp = n, cnt = 0;
			for(tmp /= prime[i]; tmp; cnt += tmp, tmp /= prime[i]);
			ans = (LL)ans * (1 + mod_pow(prime[i], cnt << 1)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
