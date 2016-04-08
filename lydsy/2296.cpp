#include <cstdio>
int t, x;
long long y, z;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &x);
		if(!x)
		{
			puts("-1");
			continue;
		}
		for(z = 1; z <= x; z *= 10);
		y = 1234567890 * z;
		z = y % x;
		if(z)
			z = x - z;
		printf("%lld\n", y + z);
	}
	return 0;
}
