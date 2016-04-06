#include <cstdio>
int n;
int phi(int x)
{
	int ret = x;
	for(int i = 2; i * i <= x; ++i)
		if(x % i == 0)
		{
			ret -= ret / i;
			while(x % i == 0)
				x /= i;
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int main()
{
	while(scanf("%d", &n) != EOF)
		printf("%d\n", phi(phi(n)));
	return 0;
}
