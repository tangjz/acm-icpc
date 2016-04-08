#include <cstdio>
#include <algorithm>
using namespace std;
const double eps = 5e-8;
const int maxn = 1000, mod = 1000000;
int t, n, tot;
long long x, ans[maxn];
double tmp;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%lf", &tmp);
		x = tmp * mod + 1e-6;
		tot = 0;
		for(long long a = 1; a <= 9; ++a)
			for(long long c = 0; c <= 9; ++c)
			{
				if((a * 10 + c) * x == (c * 10 + a) * mod)
					ans[tot++] = a * 10 + c;
				for(long long k = 1, t = 10; k <= 8; ++k, t *= 10)
				{
					long long tmp = c * (t * 10 * mod - x) + a * (mod - x * t * 10);
					if(x < mod && -tmp % (10 * (mod - x)) == 0 || x > mod && tmp % (10 * (x - mod)) == 0)
					{
						long long b = tmp / 10 / (x - mod);
						if(b >= 0 && b < t && (c * t * 10 + b * 10 + a) * mod == (a * t * 10 + b * 10 + c) * x)
							ans[tot++] = a * t * 10 + b * 10 + c;
					}
				}
			}
		sort(ans, ans + tot);
		printf("%d\n", tot);
   		for(int i = 0; i < tot; ++i)
   			printf("%I64d%c", ans[i], " \n"[i == tot - 1]);
	}
	return 0;
}
