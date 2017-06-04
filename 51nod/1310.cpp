#include <stdio.h>
typedef long long LL;
const int maxn = 50001, maxm = 87, mod = 1000000007;
int n, ans;
LL fib[maxm], a[maxn];
int main()
{
	fib[0] = 1;
	fib[1] = 2;
	for(int i = 2; i < maxm; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	for(int i = maxm - 1; i >= 0; --i)
	{
		int o = 0;
		for(int j = 0; j < n; ++j)
			if(a[j] >= fib[i])
			{
				a[j] -= fib[i];
				o ^= 1;
			}
		if((ans = ans << 1 | o) >= mod)
			ans -= mod;
	}
	printf("%d\n", ans);
	return 0;
}
