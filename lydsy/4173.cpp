#include <cstdio>
typedef long long LL;
const int mod = 998244353;
int calc(LL x)
{
	LL ret = x, tmp = x;
	for(LL i = 2; i <= tmp / i; ++i)
		if(tmp % i == 0)
		{
			ret -= ret / i;
			while(tmp % i == 0)
				tmp /= i;
		}
	if(tmp > 1)
		ret -= ret / tmp;
	return (ret % mod) * (x % mod) % mod;
}
int main()
{
	LL n, m;
	scanf("%lld%lld", &n, &m);
	printf("%d\n", (LL)calc(n) * calc(m) % mod);
	return 0;
}
