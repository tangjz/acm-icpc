#include <stdio.h>
int t, n;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		printf("Case #%d: %s\n", Case, n == 0 || n == 14 || n == 34 || n % 34 == 4 || n % 34 == 8 || n % 34 == 20 || n % 34 == 24 || n % 34 == 28 ? "UCOK" : "UDIN");
	}
	return 0;
}
