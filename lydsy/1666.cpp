/*
 * 怎么这么水...
 */
#include <cstdio>
int ans = 0;
long long n;
int main()
{
	scanf("%lld", &n);
	while(n != 1)
	{
		if(n & 1) n = 3 * n + 1;
		else n >>= 1;
		++ans;
	}
	printf("%d\n", ans);
	return 0;
}
