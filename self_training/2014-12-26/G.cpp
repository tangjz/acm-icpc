#include <cstdio>
int n, t;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		if(!n)
			puts("2");
		else
			printf("%d\n", n * (n + 1) / 2 + 1 + n * 2);
	}
	return 0;
}
