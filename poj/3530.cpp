#include <cstdio>
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
int exexgcd(int m, int d, int l, int r) // l <= m * x mod d <= r
{
	if(l % d == 0)
		return l / d;
	if(l / d != r / d)
		return l / d + 1;
	int g = gcd(m, d);
	if(l % g != 0 && l / g == r / g)//otherwise, m mod d <> 0
		return -1;
	int res = exexgcd(d, m % d, -r % d + d, -l % d + d);
	if(res == -1)
		return -1;
	return ((long long)res * m + l - 1) / d + 1;
}
int main()
{
	int n, m, d, l, r;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d%d%d%d", &m, &d, &l, &r);
		if(r >= m)
			r = m - 1;
		if(l > r || !(d %= m))
		{
			puts("-1");
			continue;
		}
		printf("%d\n", exexgcd(m, d, l, r));
	}
	return 0;
}
