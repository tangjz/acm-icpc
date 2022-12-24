#include <cstdio>
int n = 0, k;
double s = 0.0;
int main()
{
	scanf("%d", &k);
	do { s += 1.0 / ++n; } while(s <= k);
	printf("%d\n", n);
	return 0;
}