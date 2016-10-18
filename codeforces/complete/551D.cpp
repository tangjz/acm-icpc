#include <cstdio>
#include <cassert>
typedef long long LL;
int len, mod, sum[2], ans;
LL n, m;
struct Fib
{
	int num1, num2;
	Fib operator * (const Fib &x) const
	{
		return (Fib){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
	}
	Fib pow(LL k)
	{
		Fib ret = (Fib){1, 0}, tmp = *this;
		while(k)
		{
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A = {0, 1};
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
	scanf("%I64d%I64d%d%d", &n, &m, &len, &mod);
	sum[0] = A.pow(n + 2).num2;
	sum[1] = mod_pow(2, n) - sum[0];
	ans = len >= 62 || m < (1LL << len);
	for(int i = 0; i < len; ++i)
		ans = (LL)ans * sum[(m >> i) & 1] % mod;
    ans = (ans % mod + mod) % mod;
	printf("%d\n", ans);
	return 0;
}
