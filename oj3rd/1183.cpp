#include <cmath>
#include <cstdio>
long long x, y;
int main()
{
	while(scanf("%lld%lld", &x, &y) == 2)
	{
		while((int)log2(x) > (int)log2(y))
			x >>= 1;
		while((int)log2(x) < (int)log2(y))
			y >>= 1;
		while(x != y)
		{
			x >>= 1;
			y >>= 1;
		}
		printf("%lld\n", x);
	}
	return 0;
}
