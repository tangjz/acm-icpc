#include <cstdio>
int n, m, x, y, a, b;
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
int min(int x, int y)
{
	return x < y ? x : y;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	int r, d, x1, y1;
	scanf("%d%d%d%d%d%d", &n, &m, &x, &y, &a, &b);
	r = gcd(a, b);
	a /= r;
	b /= r;
	d = min(n / a, m / b);
	x1 = min(max(x - (a * d + 1) / 2, 0), n - a * d);
	y1 = min(max(y - (b * d + 1) / 2, 0), m - b * d);
	printf("%d %d %d %d\n", x1, y1, x1 + a * d, y1 + b * d);
	return 0;
}
