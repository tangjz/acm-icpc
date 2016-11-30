#include <cstdio>
typedef long long LL;
int Case;
LL n, ans;
int main()
{
	while(scanf("%lld", &n) == 1)
	{
		ans = 0;
		for(LL i = 1; i * i * i <= n; ++i)
			for(LL j = i; i * j * j <= n; ++j)
				if(i == j)//i = j = k(1), i = j < k(3)
					ans += 1 + 3 * (n / i / j - j);
				else//i < j = k(3), i < j < k(6)
					ans += 3 + 6 * (n / i / j - j);
		printf("Case %d: %lld\n", ++Case, ans);
	}
	return 0;
}
