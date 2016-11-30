#include <stdio.h>
typedef long long LL;
int t;
LL n, ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		ans = 1;
		for(LL i = 2; i * i <= n; ++i)
			if(n % i == 0)
				for(ans = i, n /= i; n % i == 0; n /= i);
		if(n > 1)
			ans = n;
		printf("%lld\n", ans);
	}
	return 0;
}
