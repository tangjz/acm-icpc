#include <cmath>
#include <cstdio>
const double pi = acos(-1);
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		printf("Property %d: This property will begin eroding in year %d.\n", i, (int)ceil(pi * (x * x + y * y) / 100));
	}
	puts("END OF OUTPUT.");
	return 0;
}
