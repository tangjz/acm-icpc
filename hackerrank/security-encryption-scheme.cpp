#include <stdio.h>
int n, ans;
int main()
{
	scanf("%d", &n);
	ans = 1;
	for(int i = 2; i <= n; ++i)
		ans *= i;
	printf("%d\n", ans);
	return 0;
}
