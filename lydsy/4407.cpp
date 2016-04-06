#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5000001, mod = 1000000007;
int t, ex, tot, prime[maxn >> 3], f[maxn], n, m, ans;
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
	scanf("%d%d", &t, &ex);
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = mod_pow(i, ex) - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j])
				f[i * prime[j]] = (LL)f[i] * f[prime[j]] % mod;
			else
			{
				f[i * prime[j]] = (LL)f[i] * (f[prime[j]] + 1) % mod;
				break;
			}
	}
	for(int i = 2; i < maxn; ++i)
	{
		f[i] += f[i - 1];
		if(f[i] >= mod)
			f[i] -= mod;
	}
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n > m)
			swap(n, m);
		ans = 0;
		for(int i = 1, j; i <= n; i = j + 1)
		{
			j = min(n / (n / i), m / (m / i));
			ans = (ans + (LL)(f[j] - f[i - 1]) * (n / i) % mod * (m / i)) % mod;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
