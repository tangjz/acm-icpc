#include <stdio.h>
typedef long long LL;
const int maxn = 10000001, mod = 1000000007;
int tot, prime[maxn / 12], d[maxn], sum[maxn];
inline int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!d[i])
		{
			prime[++tot] = i;
			d[i] = tot;
			sum[tot] = 1;
		}
		for(int j = 1, k = (maxn - 1) / i; prime[j] <= k; ++j)
		{
			d[i * prime[j]] = j;
			if(d[i] == j)
				break;
		}
	}
	int n, x, ans = 1;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		for(int pdx = d[x]; pdx; pdx = d[x])
		{
			int val = prime[pdx], cnt = val + 1;
			for(x /= prime[pdx]; x % prime[pdx] == 0; x /= prime[pdx], val *= prime[pdx], cnt += val);
			sum[pdx] = (LL)sum[pdx] * cnt % mod;
		}
	}
	for(int i = 1; i <= tot; ++i)
	{
		if(sum[i] == 1)
			continue;
		int val = sum[i] - 1;
		val = (val - (LL)val * mod_inv(prime[i]) + 1) % mod;
		ans = (LL)ans * val % mod;
	}
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
