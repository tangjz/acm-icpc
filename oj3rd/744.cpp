#include <cstdio>
int t, p, q, v[7], a, r;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &p);
		for(int i = 0; i < 7; ++i)
			scanf("%d", v + i);
		q = 0;
		for(int i = 0; i < 7; ++i)
		{
			scanf("%d", &a);
			q += v[i] * a;
		}
		r = gcd(p, q);
		p /= r;
		q /= r;
		printf("%d/%d\n", q - p, q);
		puts((q >= p << 1) ? "Yes! The real half-price!" : "No! The KFC is kidding me!");
	}
	return 0;
}
