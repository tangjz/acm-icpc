#include <stdio.h>
typedef long long LL;
const int maxn = 101;
int tot, last;
LL n, fib[maxn];
int main()
{
	scanf("%lld", &n);
	tot = 2;
	fib[0] = 1;
	fib[1] = 2;
	for( ; fib[tot - 1] < n; ++tot)
		fib[tot] = fib[tot - 1] + fib[tot - 2];
	for(int i = tot - 1; i >= 0; --i)
		if(n >= fib[i])
		{
			n -= fib[i];
			last = i;
		}
	printf("%lld\n", fib[last]);
	return 0;
}
