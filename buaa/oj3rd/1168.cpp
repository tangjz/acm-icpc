#include <cstdio>
long long x;
int main()
{
	while(scanf("%lld", &x) == 1)
		printf("%lld\n", x * x * x - (x > 2 ? (x - 2) * (x - 2) * (x - 2) : 0));
	return 0;
}
