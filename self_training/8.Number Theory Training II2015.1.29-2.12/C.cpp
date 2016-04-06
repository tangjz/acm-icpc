#include <cstdio>
typedef long long LL;
int t, n;
LL now, ans;
LL gcd(LL a, LL b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 1;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%I64d", &now);
			ans *= now / gcd(ans, now);
		}
		if(ans <= 1e9)
			printf("%I64d\n", ans);
		else
			puts("More than a billion.");
	}
	return 0;
}
