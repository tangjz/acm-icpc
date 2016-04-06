#include <cstdio>
int a, b;
int main()
{
	scanf("%d%d", &a, &b);
	for(int i = 1; i <= a; ++i)
		printf("%d ", i);
	for(int i = a + b + 1; i > a; --i)
		printf("%d ", i);
	putchar('\n');
	return 0;
}
