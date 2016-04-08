#include <cstdio>
typedef long long LL;
int t;
LL a, b, c, d;
LL gcd(LL x, LL y)
{
	return y ? gcd(y, x % y) : x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		puts(gcd(a, b) == gcd(c, d) ? "Yes" : "No");
	}
	return 0;
}
