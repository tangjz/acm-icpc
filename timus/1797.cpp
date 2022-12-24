#include <stdio.h>
typedef long long LL;
inline LL gcd(LL x, LL y)
{
	LL r = x % y;
	while(r)
	{
		x = y;
		y = r;
		r = x % y;
	}
	return y;
}
inline LL solve(LL n, LL x, LL y)
{
	LL r = gcd(x, y), ret = 0;
	n /= r;
	x /= r;
	y /= r;
	if(x == 1)
		return n + 1;
	if(n / (x - 1) >= y - 1)
	{
		ret = n - (x - 1) * (y - 1) + 1;
		n -= ret;
	}
	while(1)
	{
		LL m = n / y, a = y / x, b = y - a * x, delta = (n - m * b) / x;
		ret -= m * (m + 1) / 2 * a;
		if(!b)
		{
			ret += (n + 1) * (m + 1);
			break;
		}
		ret += delta * (m + 1);
		n -= delta * x;
		y = x;
		x = b;
		ret -= n / x - m;
	}
	return ret;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		LL x, y, L, R;
		scanf("%I64d%I64d%I64d%I64d", &x, &y, &L, &R);
		printf("%I64d\n", solve(R, x, y) - solve(L - 1, x, y));
	}
	return 0;
}