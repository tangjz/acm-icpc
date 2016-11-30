#include <cstdio>
int t, n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		if(!n)
			puts("1");
		else
		{
			putchar('5');
			for(int i = 1; i < n; ++i)
				putchar('0');
			putchar('5');
			for(int i = 1; i < n; ++i)
				putchar('0');
			putchar('\n');
		}
	}
	return 0;
}
