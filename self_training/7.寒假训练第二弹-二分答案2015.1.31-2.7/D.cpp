#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10010, maxt = 233;
const double eps = 1e-8, pi = acos(-1);
int t, n;
double a[maxn], ans;
double sqr(double x)
{
	return x * x;
}
int check(double r)
{
	double tri = 0, goa;
	for(int i = 0; i < n; ++i)
	{
		if(a[i] > 2 * r)
			return 1;
		double theta = acos(1 - sqr(a[i] / r) / 2);
		if(i + 1 == n)
		{
			if(tri < pi)
			{
				goa = tri;
				tri = theta;
			}
			else
			{
				goa = 2 * pi;
				tri += theta;
			}
		}
		else
			tri += theta;
	}
	if(fabs(tri - goa) < eps)
		return 0;
	return tri < goa ? -1 : 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%lf", a + i);
		sort(a, a + n);
		double L = 0, R = 1e4, M;
		bool flag = 0;
		for(int tt = 0; tt < maxt; ++tt)
		{
			M = (L + R) / 2;
			int res = check(M);
			if(!res)
			{
				flag = 1;
				break;
			}
			if(res > 0)
				L = M;
			else
				R = M;
		}
		if(!flag)
		{
			puts("0.000");
			continue;
		}
		ans = 0;
		double tri = 0;
		for(int i = 0; i < n; ++i)
		{
			if(a[i] > 2 * M)
				return 1;
			double theta = acos(1 - sqr(a[i] / M) / 2);
			double area = sqr(M) * sin(theta) / 2; 
			if(i + 1 == n)
				ans += tri < pi ? -area : area;
			else
			{
				tri += theta;
				ans += area;
			}
		}
		printf("%.3f\n", ans);
	}
	return 0;
}
