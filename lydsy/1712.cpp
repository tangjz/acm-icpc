#include <cstdio>
typedef long long LL;
const int maxn = 50001, mod = 98765431;
int n, a[maxn], sum;
LL t;
int inv(int x)
{
	return x <= 1 ? x : mod - (LL)mod / x * inv(mod % x) % mod;
}
int mod_pow(int x, LL k)
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
	scanf("%d%lld", &n, &t);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		sum += a[i];
		if(sum >= mod)
			sum -= mod;
	}
	sum = (LL)(mod_pow(n - 1, t) - (t & 1 ? -1 : 1)) * inv(n) % mod * sum % mod;
	if(sum < 0)
		sum += mod;
	for(int i = 0; i < n; ++i)
	{
		a[i] = t & 1 ? sum + mod - a[i] : sum + a[i];
		if(a[i] >= mod)
			a[i] -= mod;
		printf("%d\n", a[i]);
	}
	return 0;
}
