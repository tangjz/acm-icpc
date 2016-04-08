#include <cstdio>
typedef long long LL;
const int maxp = 316228;
int mu[maxp];
LL calc_3(LL n)
{
	LL ret = 0;
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
	for(LL i = 1; i * i <= n; ++i)
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
	LL a, b;
	scanf("%lld%lld", &a, &b);
	printf("%lld\n", calc(b) - calc(a - 1));
	return 0;
}
