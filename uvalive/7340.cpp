#include <stdio.h>
typedef long long LL;
int main()
{
	for(int n; scanf("%d", &n) == 1 && n; )
	{
		LL ans = -1;
		for(int i = 1, j, k; i <= n; i = j + 1)
		{
			k = n / i;
			j = n / k;
			ans += ((j - i + 1LL) * (i + j) >> 1) * k;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
