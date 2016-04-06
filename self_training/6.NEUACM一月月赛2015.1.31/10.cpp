#include <cstdio>
int n;
int main()
{
	while(scanf("%d", &n) != EOF)
		printf("%d\n", n + 1 >> 1);
	return 0;
}
