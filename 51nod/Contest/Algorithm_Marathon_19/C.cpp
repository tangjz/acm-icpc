#include <stdio.h>
typedef long long LL;
const int mod = 1000000007;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	LL x;
	scanf("%*lld%*lld%lld", &x);
	printf("%d\n", mod_pow(2, x % (mod - 1)));
	return 0;
}
