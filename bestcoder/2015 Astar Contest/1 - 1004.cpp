#include <cmath>
#include <cstdio>
const char* ans[] = {"I want to kiss you!", "Give me a kiss!"};
const double pi = acos(-1.0), eps = 1e-8;
int t, n;
double a, r;
int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%lf%lf", &n, &a, &r);
		printf("Case #%d:\n%s\n", Case, ans[dcmp(a / 2 / tan(pi / n) - r) >= 0]);
	}
	return 0;
}
