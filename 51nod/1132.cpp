#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL solve(LL n, LL x, LL y)
{
	LL r = __gcd(x, y), ret = 0;
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
		scanf("%lld%lld%lld%lld", &x, &y, &L, &R);
		printf("%lld\n", solve(R, x, y) - solve(L - 1, x, y));
	}
	return 0;
}
