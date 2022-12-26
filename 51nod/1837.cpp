#include <cmath>
//#include <cassert>
#include <stdio.h>
typedef long long LL;
const int maxt = 100000, maxn = 1000000000L;
int n;
bool is_triple(int x)
{
	int a = sqrt(x << 1), b = (a * (a + 1)) >> 1;
	for( ; b + a + 1 <= x; b += ++a);
	for( ; b > x; b -= a--);
	return b == x;
}
bool is_square(LL x)
{
	LL a = sqrtl(x), b = a * a;
	for( ; b + (a << 1 | 1) <= x; b += (a++) << 1 | 1);
	for( ; b > x; b -= (--a) << 1 | 1);
	return b == x;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		//static int Case = 0;
		//assert(++Case <= maxt && 0 < n && n <= maxn);
		puts(n == 1 ? "0" : is_triple(n) || is_triple(n - 1) || is_square(n * (n + 1LL) >> 1) || is_square((n * (n + 1LL) >> 1) - 1) ? "1" : "2");
	}
	return 0;
}
