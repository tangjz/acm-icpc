#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int a, b, n;
int main()
{
	for(int Case = 1; scanf("%d%d%d", &a, &b, &n) == 3 && a + b + n; ++Case)
	{
		int r = __gcd(a, b);
		a /= r;
		b /= r;
		if(b <= n)
		{
			printf("Case %d: %d/%d %d/%d\n", Case, a, b, a, b);
			continue;
		}
		int x1 = 0, y1 = 1, x2, y2, x3 = 1, y3 = 1;
		for(x2 = x1 + x3, y2 = y1 + y3; y2 <= n; x2 = x1 + x3, y2 = y1 + y3)
		{
			bool flag = (LL)a * y2 > (LL)b * x2;
			(flag ? x1 : x3) = x2;
			(flag ? y1 : y3) = y2;
		}
		printf("Case %d: %d/%d %d/%d\n", Case, x1, y1, x3, y3);
	}
	return 0;
}
