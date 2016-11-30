#include <cstdio>
int t, n, r, x;
double s;
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lf%d%d", &s, &n, &r);
		s *= 4;
		while(--n)
		{
			scanf("%d", &x);
			r = gcd(r, x);
		}
		while(~r & 1)
			r >>= 1;
		puts(s <= (int)s + 1e-6 && (int)s % r == 0 ? "yes" : "no");
	}
	return 0;
}
