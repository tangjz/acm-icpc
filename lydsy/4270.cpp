#include <cstdio>
typedef long long LL;
LL gcd(LL x, LL y)
{
	return y ? gcd(y, x % y) : x;
}
LL exexgcd(LL m, LL d, LL l, LL r) // l <= m * x mod d <= r
{
	if(l % d == 0)
		return l / d;
	if(l / d != r / d)
		return l / d + 1;
	LL g = gcd(m, d);
	if(l % g != 0 && l / g == r / g)//otherwise, m mod d <> 0
		return -1;
	LL res = exexgcd(d, m % d, -r % d + d, -l % d + d);
	if(res == -1)
		return -1;
	return (res * m + l - 1) / d + 1;
}
int main()
{
	int n;
	LL m, d, l, r;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%lld%lld%lld%lld", &m, &d, &l, &r);
		if(r >= m)
			r = m - 1;
		if(l > r || !(d %= m))
		{
			puts("-1");
			continue;
		}
		printf("%lld\n", l ? exexgcd(m, d, l, r) : 0);
	}
	return 0;
}
