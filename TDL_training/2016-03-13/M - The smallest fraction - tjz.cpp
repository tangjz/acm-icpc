#include <cstdio>
typedef long long LL;
int n, a[6], b[6];
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		LL p = 1;
		int q = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", a + i, b + i);
			int r = gcd(a[i], b[i]);
			a[i] /= r;
			b[i] /= r;
			q = gcd(b[i], q);
			p = p / gcd(a[i], p % a[i]) * a[i];
		}
		printf("%lld %d\n", p, q);
	}
	return 0;
}
