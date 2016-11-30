#include <stdio.h>
typedef long long LL;
const int mod = 1000000007;
int n, a, b, ans;
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
	while(scanf("%d%d%d", &n, &a, &b) == 3)
	{
		if(b % a != 0)
		{
			puts("0");
			continue;
		}
		b /= a;
		ans = 1;
		for(int i = 2, c; i <= b / i; ++i)
			if(b % i == 0)
			{
				for(c = 0; b % i == 0; b /= i, ++c);
				ans = (LL)ans * (mod_pow(c + 1, n) - 2LL * mod_pow(c, n) + mod_pow(c - 1, n)) % mod;
			}
		if(b > 1)
			ans = (LL)ans * (mod_pow(2, n) - 2) % mod;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
