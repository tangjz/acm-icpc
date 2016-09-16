#include <stdio.h>
int main()
{
	int n, k, ans = 1;
	scanf("%d", &n);
	for(k = n, n %= 10; k > 0; k >>= 1, n = n * n % 10)
		if(k & 1)
			ans = ans * n % 10;
	printf("%d\n", ans);
	return 0;
}
