#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 91, mod = 1000000007;
int t, len;
LL fib[maxn], n;
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	fib[1] = 1;
	for(int i = 2; i < maxn; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
	for(int i = 2; i < maxn; ++i)
		fib[i] |= fib[i - 1];
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		if(n < maxn)
			printf("%d\n", (int)(fib[n] % mod));
		else
		{
			len = (int)(n * (log2(1 + sqrt(5)) - 1) - log2(sqrt(5)) + 1);
			printf("%d\n", mod_pow(2, len) - 1);
		}
	}
	return 0;
}
