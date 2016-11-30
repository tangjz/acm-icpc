#include <stdio.h>
typedef long long LL;
const int mod = 1000000007;
int t;
LL n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		n %= mod;
		printf("%d\n", (int)(n * n % mod));
	}
	return 0;
}
