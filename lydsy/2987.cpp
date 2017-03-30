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
	if(x > y)
		swap(x, y);
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
	LL x, y, n;
	while(scanf("%lld%lld%lld", &x, &y, &n) == 3)
		printf("%lld\n", solve(n, x, y));
	return 0;
}
