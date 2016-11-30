#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 500001, mod = 1000000007;
int n, m, pw[maxn], s[maxn], mu[maxn];
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	if(n > m)
		std::swap(n, m);
	mu[1] = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = i + i; j <= n; j += i)
			mu[j] -= mu[i];
	for(int i = 1; i <= m; ++i)
		pw[i] = 1;
	int ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		int nlim = n / i, mlim = m / i, sum = 0;
		for(int j = 1; j <= mlim; ++j)
		{
			pw[j] = (LL)pw[j] * j % mod;
			if((s[j] = s[j - 1] + pw[j]) >= mod)
				s[j] -= mod;
		}
		for(int j = 1; j <= nlim; ++j)
			if(mu[j])
				sum = (sum + (LL)pw[j] * pw[j] % mod * s[nlim / j] % mod * s[mlim / j] * mu[j]) % mod;
		ans = (ans + (LL)mod_pow(i, i) * sum) % mod;
	}
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
