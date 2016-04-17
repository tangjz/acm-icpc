#include <cstdio>
typedef unsigned int UL;
const int maxd = 32;
void Add(UL &x, int dig)
{
	UL val = 0;
	for(int now = 0; now < maxd; now += dig)
		val |= (x - (val << dig)) & (((1u << dig) - 1) << now);
	x = val;
}
void Xor(UL &x, int dig)
{
	UL val = 0;
	for(int now = maxd; now > 0; now -= dig)
		val |= (x ^ (val >> dig)) & (now >= dig ? ((1u << dig) - 1) << now - dig : ((1u << dig) - 1) >> dig - now);
	x = val;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		UL x;
		scanf("%u", &x);
		Add(x, 16);
		Xor(x, 11);
		Add(x, 3);
		Xor(x, 6);
		Add(x, 10);
		printf("%u\n", x);
	}
	return 0;
}
