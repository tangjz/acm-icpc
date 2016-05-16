#include <stdio.h>
#include <algorithm>
const int maxn = 5, ans[maxn] = {153, 370, 371, 407, 1634};
int num;
int main()
{
	scanf("%d", &num);
	printf("%d\n", *std::lower_bound(ans, ans + maxn, num));
	return 0;
}
