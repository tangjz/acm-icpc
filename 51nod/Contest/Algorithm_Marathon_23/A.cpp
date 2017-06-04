#include <stdio.h>
const int len = 6, ans[len] = {2, 1, -1, -2, -1, 1};
long long n;
int main()
{
	scanf("%lld", &n);
	printf("%d\n", ans[(int)(n % len)]);
	return 0;
}
