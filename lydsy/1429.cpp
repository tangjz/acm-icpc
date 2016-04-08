#include <cstdio>
typedef long long LL;
LL n, ans;
int main()
{
	scanf("%lld", &n);
	n = (n << 1) + 1;
	ans = n + 1;
	for(LL i = 3; i <= n / i; ++i)
		if(n % i == 0)
		{
			ans += i;
			if(i != n / i)
				ans += n / i;
		}
	printf("%lld\n", ans);
	return 0;
}
