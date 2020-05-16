#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int a, b, c, d;
double ans, tmp1, tmp2;
int main()
{
	while(scanf("%d%d%d%d", &a, &b, &c, &d) != EOF)
	{
		ans = 0.0;
		tmp1 = (double)a / b;
		tmp2 = (double)(b - a) / b * (double)(d - c) / d;
		while(tmp1 > 1e-20)
		{
			ans += tmp1;
			tmp1 *= tmp2;
		}
		printf("%.14lf\n", ans);
	}
	return 0;
}
