#include <cstdio>
typedef long long LL;
const int maxn = 10000001, mod = 100000009;
int tot, prime[maxn], f[maxn];
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = 1 - i;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				f[i * prime[j]] = f[i];
				break;
			}
			else
				f[i * prime[j]] = f[i] * f[prime[j]];
	}
	for(int i = 2; i < maxn; ++i)
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	int t, n, m, ans;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n > m)
		{
			n = n + m;
			m = n - m;
			n = n - m;
		}
		ans = 0;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i) < m / (m / i) ? n / (n / i) : m / (m / i);
			ans = (ans + ((n / i) * (n / i + 1LL) / 2 % mod) * ((m / i) * (m / i + 1LL) / 2 % mod) % mod * (f[j] - f[i - 1])) % mod;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
