#include <stdio.h>
typedef long long LL;
const long double coeff = 1.618033988749894848204586834;
const int sei[3] = {618033988, 749894848, 204586834}, delta = 1000000000;
int t;
LL a, b;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &a, &b);
		if(a > b)
		{
			a = a + b;
			b = a - b;
			a = a - b;
		}
		b -= a;
		if(a <= b || a >= b << 1)
		{
			puts("A");
			continue;
		}
		int bH = b / delta, bL = b % delta;
		LL x = (((LL)bL * sei[2] / delta + (LL)bH * sei[2] + (LL)bL * sei[1]) / delta + (LL)bH * sei[1] + (LL)bL * sei[0]) / delta + (LL)bH * sei[0] + b;
		puts(a != x ? "A" : "B");
	}
	return 0;
}
