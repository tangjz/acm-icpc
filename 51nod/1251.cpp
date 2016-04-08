#include <stdio.h>
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int t, n, m, fact[maxn << 1], inv[maxn], ans;
inline int C(int n, int m)
{
	return (LL)fact[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxn << 1; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (LL)mod / i * inv[mod % i] % mod;
	inv[0] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(m == 1)
		{
			puts("1");
			continue;
		}
		ans = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1, k = n / i < m ? n / i : m; j <= k; ++j)
				ans = (ans + ((j - 1) & 1 ? -1LL : 1LL) * C(m - 1, j - 1) * C(n - i * j + m - 2, n - i * j)) % mod;
		ans = (LL)ans * m % mod;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
