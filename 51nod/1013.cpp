#include <stdio.h>
typedef long long LL;
const int mod = 1000000007;
int main()
{
	int x = 3, k, ans = 1;
	scanf("%d", &k);
	for(++k; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ans = (LL)ans * x % mod;
	ans = (ans - 1LL) * (mod + 1 >> 1) % mod;
	printf("%d\n", ans);
	return 0;
}
