#include <stdio.h>
int n;
int main()
{
	scanf("%d", &n);
	if(n & 1)
	{
		puts("0");
		return 0;
	}
	for(int i = 1; i < n; ++i)
		printf("%d%c", n - i, " \n"[i == n - 1]);
	for(int i = 0; i < n >> 1; ++i)
	{
		if(i)
			printf("%d ", i);
		printf("%d%c", (n >> 1) + i, " \n"[i == (n >> 1) - 1]);
	}
	return 0;
}
