#include <cmath>
#include <cstdio>
const double pi = acos(-1);
double a, b;
int main()
{
	while(scanf("%lf%lf", &a, &b) == 2)
		printf("%d\n", (int)ceil(pi / asin(b / (a + b))));
	return 0;
}
