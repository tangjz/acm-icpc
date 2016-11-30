#include <cmath>
#include <stdio.h>
typedef long long LL;
const int maxp = 1000001;
int mu[maxp];
LL calc_3(LL n)
{
	static LL lastn = -1, ret;
	if(lastn == n)
		return ret;
	lastn = n;
	ret = 0;
	for(LL x = 1; x * x * x <= n; ++x)
	{
		ret += 1 + 3 * (n / x / x - x);
		for(LL y = x + 1; x * y * y <= n; ++y)
			ret += 3 + 6 * (n / x / y - y);
	}
	return ret;
}
LL calc(LL n)
{
	LL ret = n;
	for(LL i = 1, j = (LL)sqrt(n); i <= j; ++i)
		if(mu[i])
			ret += mu[i] * calc_3(n / i / i);
	return ret >> 1;
}
int main()
{
	mu[1] = 1;
	for(int i = 1; i < maxp; ++i)
		for(int j = i << 1; j < maxp; j += i)
			mu[j] -= mu[i];
	LL n;
	while(scanf("%lld", &n) == 1)
		printf("%lld\n", calc(n));
	return 0;
}
