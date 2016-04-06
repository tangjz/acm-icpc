#include <cstdio>
int n, a, b, c;
int main()
{
	scanf("%d", &n);
	while(c <= n)
	{
		++a;
		b += a;
		c += b;
	}
	printf("%d\n", --a);
	return 0;
}
