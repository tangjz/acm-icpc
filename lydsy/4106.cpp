#include <cmath>
#include <cstdio>
int p, a, b, c, d, n;
double last, now, ans;
int main()
{
	while(scanf("%d%d%d%d%d%d", &p, &a, &b, &c, &d, &n) == 6)
	{
		ans = 0;
		last = sin(a + b) + cos(c + d);
		for(int i = 2; i <= n; ++i)
		{
			now = sin(a * i + b) + cos(c * i + d);
			if(ans < last - now)
				ans = last - now;
			if(last < now)
				last = now;
		}
		printf("%.6f\n", ans * p);
	}
	return 0;
}
