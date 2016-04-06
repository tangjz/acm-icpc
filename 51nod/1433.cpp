#include <stdio.h>
int n, x, c0, c5;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		x ? ++c5 : ++c0;
	}
	if(c5 >= 9 && c0)
	{
		for(int i = 9; i <= c5; i += 9)
			for(int j = 0; j < 9; ++j)
				putchar('5');
		for(int i = 1; i <= c0; ++i)
			putchar('0');
		putchar('\n');
	}
	else if(c0)
		puts("0");
	else
	    puts("-1");
	return 0;
}
