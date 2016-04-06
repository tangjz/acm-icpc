#include <cstdio>
double n;
int main()
{
	while(scanf("%lf", &n) == 1)
		printf("%.3f\n", n * (n - 1) / 8);
	return 0;
}
