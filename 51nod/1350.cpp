#include <stdio.h>
typedef long long LL;
const int maxf = 84;
int t;
LL n, fib[maxf], res[maxf], ans;
int main()
{
	fib[1] = 1;
	for(int i = 2; i < maxf; ++i)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
		res[i] = res[i - 1] + res[i - 2] + fib[i - 2];
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		ans = 0;
		for(int i = maxf - 1; i > 1; --i)
			if(n >= fib[i])
			{
				ans += res[i] + n - fib[i] + 1;
				n -= fib[i];
			}
		printf("%lld\n", ans);
	}
	return 0;
}
