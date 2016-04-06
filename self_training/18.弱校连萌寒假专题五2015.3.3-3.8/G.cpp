#include <cstdio>
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
int x, y, m, n, l, r;
int main()
{
	while(scanf("%d%d%d%d%d", &x, &y, &m, &n, &l) == 5)
	{
		m = (m - n) % l;
		if(m < 0)
			m += l;
		n = (y - x) % l;
		if(n < 0)
			n += l;
		r = exgcd(m, l, x, y);
		if(x < 0)
			x += l;
		if(n % r != 0)
			puts("Impossible");
		else
			printf("%d\n", (int)((long long)n / r * x % (l / r)));
	}
	return 0;
}
