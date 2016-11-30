#include <cstdio>
int t, n;
double d, a, b, f;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%lf%lf%lf%lf", &n, &d, &a, &b, &f);
		printf("%d %.2f\n", n, d * f / (a + b));
	}
	return 0;
}
