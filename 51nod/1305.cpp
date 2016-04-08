#include <stdio.h>
typedef long long LL;
int n, x, s1, s2;
LL ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &x);
		if(x == 1)
			++s1;
		else if(x == 2)
			++s2;
	}
	printf("%lld\n", s1 * (n - 1LL) + (s2 * (s2 - 1LL) >> 1));
	return 0;
}
