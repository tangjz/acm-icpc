#include <stdio.h>
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	if(n & 1)
		if(m & 1)
			printf("%d\n", ((n - 1) / m + 1) | 1);
		else
			puts("-1");
	else
		if(m & 1)
			if(m << 1 <= n)
				printf("%d\n", ((n - 1) / m + 2) & (~0u << 1));
			else
				printf("%d\n", ((n - 1) / (n - m) + 2) & (~0u << 1));
		else
			if(m << 1 <= n)
				printf("%d\n", (n - 1) / m + 1);
			else
				puts("3");
	return 0;
}
