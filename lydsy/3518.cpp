#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 50001, mod = 1000000007;
int n, m, tot, pr[maxn], d[maxn], f[maxn], ans;
inline int g(int n, int x)
{
	return (((LL)(n - x + n % x) * (n / x)) >> 1) % mod;
}
int main()
{
	scanf("%d%d", &n, &m);
	if(n > m)
		std::swap(n, m);
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				f[k] = f[i] * pr[j];
				break;
			}
			else
				f[k] = f[i] * (pr[j] - 1);
		}
	}
	for(int i = 1; i <= n; ++i)
		ans = (ans + (LL)f[i] * g(n, i) % mod * g(m, i)) % mod;
	ans = ((ans << 1) + n * (n - 1LL) * (n - 2) / 6 * m + m * (m - 1LL) * (m - 2) / 6 * n) % mod;
	printf("%d\n", ans);
	return 0;
}
