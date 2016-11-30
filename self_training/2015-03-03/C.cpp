#include <cstdio>
const int mod = 1000000;
int t;
long long n, ans1, ans2;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%I64d", &n);
		ans1 = 8 * n - 7;
		ans2 = ans1 % mod * n + 1;
		ans1 = ans1 / mod * n;
		ans1 += ans2 / mod;
		ans2 %= mod;
		if(ans1)
			printf("Case #%d: %I64d%06I64d\n", Case, ans1, ans2);
		else
			printf("Case #%d: %I64d\n", Case, ans2);
	}
	return 0;
}
