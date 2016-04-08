#include <cstdio>
typedef long long LL;
const LL mod = 1000000007, inv2 = 500000004;
LL n, ans;
int main()
{
	//n % i = n - [n / i] * i
	scanf("%lld", &n);
	ans = (n % mod) * (n % mod) % mod;
	for(LL i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		if(j > n)
			j = n;
		ans -= (n / i % mod) * ((i + j) % mod) % mod * ((j - i + 1) % mod) % mod * inv2 % mod;
		if(ans < 0)
			ans += mod;
	}
	printf("%lld\n", ans);
	return 0;
}
