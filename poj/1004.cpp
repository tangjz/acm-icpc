#include <cstdio>
double tmp, ans;
int main()
{
	for(int i = 0; i < 12; ++i) scanf("%lf", &tmp), ans += tmp;
	printf("$%.2f\n", ans / 12);
	return 0;
}
