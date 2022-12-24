#include <cstdio>
typedef long long LL;
int t, mod;
LL n;
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
int mod_sum(int x, LL k, int& xk)
{
	if(k == 1)
	{
		xk = x;
		return 1;
	}
	int ret = mod_sum(x, k >> 1, xk);
	ret = (LL)ret * (1 + xk) % mod;
	xk = (LL)xk * xk % mod;
	if(k & 1)
	{
		ret += xk;
		if(ret >= mod)
			ret -= mod;
		xk = (LL)xk * x % mod;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		int ans = 0, tmp;
		scanf("%lld%d", &n, &mod);
		for(int i = 1; i < mod && i <= n; ++i)
			ans = (ans + (LL)mod_pow(i, i) * mod_sum(mod_pow(i, mod), (n - i) / mod + 1, tmp)) % mod;
		printf("%d\n", ans);
	}
	return 0;
}