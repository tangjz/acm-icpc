#include <cstdio>
#include <algorithm>
int t;
long long a, b, c, d, r;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &a, &b);
		c = a + b * 3;
		d = (a + b) * 4;
		r = std::__gcd(c, d);
		printf("%lld/%lld\n", c / r, d / r);
	}
	return 0;
} 
