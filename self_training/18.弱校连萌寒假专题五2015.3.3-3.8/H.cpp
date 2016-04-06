#include <cstdio>
long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
long long a, b, c, d, k, r;
int main()
{
	while(scanf("%lld%lld%lld%lld", &a, &b, &c, &k) == 4 && a + b + c + k)
	{
		k = 1LL << k;
		d = (b - a) % k;
		if(d < 0)
			d += k;
		r = exgcd(c, k, a, b);
		if(a < 0)
			a += k;
		if(d % r != 0)
			puts("FOREVER");
		else
			printf("%lld\n", d / r * a % (k / r));
	}
	return 0;
}
