#include <cstdio>
const int mod = 1000000007, maxm = 1000001;
typedef long long LL;
int inv[maxm], ans;
LL n, m;
int main()
{
	scanf("%lld%lld", &n, &m);
	if(n > m)
	{
		n = n + m;
		m = n - m;
		n = n - m;
	}
	ans = (n + m + 1) % mod;
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
		ans = (n + m + 2 - i) % mod * ans % mod * inv[i] % mod;
	}
	ans = (ans + m) % mod;
	printf("%d\n", ans);
	return 0;
}