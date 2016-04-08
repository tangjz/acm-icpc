#include <stdio.h>
typedef long long LL;
const int maxn = 50001, maxa = 1000001, mod = 1000000007;
int n, x, cnt[maxa], fib[maxa], ans = 1;
bool vis[maxa];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	fib[1] = 1;
	for(int i = 2; i < maxa; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
		if(fib[i] >= mod)
			fib[i] -= mod;
	}
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &x);
		vis[x] = 1;
	}
	for(int i = maxa - 1; i > 2; --i)
	{
		for(int j = i + i; j < maxa && !vis[i]; j += i)
			vis[i] |= vis[j];
		if(!vis[i])
			continue;
		cnt[i] = 1;
		for(int j = i + i; j < maxa; j += i)
			cnt[i] -= cnt[j];
		int tmp = cnt[i] % (mod - 1);
		if(tmp < 0)
			tmp += mod - 1;
		if(tmp)
			ans = (LL)ans * mod_pow(fib[i], tmp) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
