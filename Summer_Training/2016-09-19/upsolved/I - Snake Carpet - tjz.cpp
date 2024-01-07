#include <stdio.h>
void print(int n)
{
	if(n == 2)
	{
		puts("1 1");
		puts("1 2 1 3");
	}
	else if(n == 3)
	{
		puts("1 1");
		puts("2 1 2 2");
		puts("1 2 1 3 2 3");
	}
	else if(n & 1)
	{
		print(n - 3);
		for(int i = n + 1 >> 1; i <= n - 2; ++i)
			printf("%d %d ", n - 1 >> 1, i);
		for(int i = n - 1 >> 1; i >= 1; --i)
			printf("%d %d%c", i, n - 1, " \n"[i == 1]);
		for(int i = 1; i <= n - 1 >> 1; ++i)
			printf("%d %d ", n - 1 >> 1, i);
		for(int i = n - 1 >> 1; i >= 1; --i)
			printf("%d %d%c", n + 1 >> 1, i, " \n"[i == 1]);
		for(int i = n + 1 >> 1; i <= n - 1; ++i)
			printf("%d %d ", n + 1 >> 1, i);
		for(int i = n + 1 >> 1; i >= 1; --i)
			printf("%d %d%c", i, n, " \n"[i == 1]);
	}
	else
	{
		print(n - 1);
		for(int i = 1; i <= n >> 1; ++i)
			printf("%d %d ", i, n);
		for(int i = n >> 1; i >= 1; --i)
			printf("%d %d%c", i, n + 1, " \n"[i == 1]);
	}
}
int main()
{
	for(int n; scanf("%d", &n) == 1; n == 1 ? (void)puts("1 1") : print(n))
		printf("%d %d\n", n + 1 >> 1, n | 1);
	return 0;
}
