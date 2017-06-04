#include <stdio.h>
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	printf("%.6f\n", ((n * (n - 1LL)) >> 1) / (double)m);
	return 0;
}
