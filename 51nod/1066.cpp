#include <stdio.h>
int t, n, k;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &k);
		puts(n % (k + 1) ? "A" : "B");
	}
	return 0;
}
