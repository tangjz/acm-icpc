#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL solve(LL n, LL x, LL y)
{
	LL a = (x - 1) / (y - x) + 1, b = n / x;
	if(a <= b)
		return a * (a - 1) / 2 * (y - x) + a - 1 + n - a * x + 1;
	return b * (b - 1) / 2 * (y - x) + b - 1 + min(n, b * y) - b * x + 1;
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
