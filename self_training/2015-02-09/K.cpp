#include <cstdio>
int n, ans, fact;
int maxfact(int x)
{
	int ret = 1;
	for(int i = 2; i * i <= x; ++i)
		if(x % i == 0)
		{
			ret = i;
			while(x % i == 0)
				x /= i;
		}
	if(x > 1)
		ret = x;
	return ret;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		ans = fact = 0;
		while(n--)
		{
			int x, now;
			scanf("%d", &x);
			if((now = maxfact(x)) > fact)
			{
				ans = x;
				fact = now;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
