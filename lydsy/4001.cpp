#include <cstdio>
long long n;
int main()
{
	scanf("%lld", &n);
	printf("%.9f\n", n * (n + 1) / 2.0 / (2 * n - 1.0));
	return 0;
}
