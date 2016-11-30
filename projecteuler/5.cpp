#include <stdio.h>
#include <algorithm>
typedef long long LL;
int t, n;
LL ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		ans = 1;
		for(int i = 2; i <= n; ++i)
			ans *= i / std::__gcd(i, (int)(ans % i));
		printf("%lld\n", ans);
	}
	return 0;
}
