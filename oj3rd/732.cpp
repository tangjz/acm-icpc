#include <cstdio>
int t, a, b;
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &a, &b);
		int x = a * (100 - b), y = 10000 - a * b;
		int r = gcd(x, y);
		x /= r, y /= r;
		printf("%d/%d %d/%d\n", x, y, y - x, y);
	}
	return 0;
}
