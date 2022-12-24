#include <cmath>
#include <cstdio>
const double pi = 3.1415926535897;
double r, X1, Y1, X2, Y2;
int main()
{
	while(scanf("%lf%lf%lf%lf%lf", &r, &X1, &Y1, &X2, &Y2) == 5)
	{
		double dist = ((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2)) / 4;
		if(dist > r * r)
		{
			printf("%.3f\n", 2 * pi * r * r);
			continue;
		}
		dist = sqrt(dist);
		double single = acos(dist / r) * 2;
		printf("%.3f\n", (2 * pi - single) * r * r + r * r * sin(single));
	}
}
