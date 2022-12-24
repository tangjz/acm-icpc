#include <cstdio>
int n;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		if(n == 1)
		{
			puts("1");
			continue;
		}
		int first = 1;
		for(int i = 2; i <= n / i; ++i)
			if(n % i == 0)
			{
				while(n % i == 0)
				{
					if(!first)
						putchar('*');
					else
						first = 0;
					printf("%d", i);
					n /= i;
				}
			}
		if(n > 1)
		{
			if(!first)
				putchar('*');
			else
				first = 0;
			printf("%d", n);
		}
		putchar('\n');
	}
	return 0;
}
