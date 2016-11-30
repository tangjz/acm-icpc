#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 23333333, mod = 999999017, inv2 = (mod + 1) >> 1, inv3 = (mod + 1) / 3;
map<LL, int> Hash;
int tot, prime[maxn], f[maxn], ans;
int calc_iphi(LL x)
{
	if(x < maxn)
		return f[(int)x];
	if(Hash.count(x))
		return Hash[x];
	int ret = x % mod * ((x + 1) % mod) % mod * (((x << 1) + 1) % mod) % mod * inv3 % mod;
	for(LL i = 2, j, k; i <= x; i = j)
	{
		k = x / i;
		j = x / k + 1;
		ret = (ret - (i + j - 1) % mod * ((j - i) % mod) % mod * calc_iphi(k)) % mod;
	}
	ret = (LL)ret * inv2 % mod;
	if(ret < 0)
		ret += mod;
	return Hash[x] = ret;
}
int calc(LL n)
{
	int ret = n % mod;
	for(LL i = 1, j, k; i <= n; i = j)
	{
		k = n / i;
		j = n / k + 1;
		ret = (ret + (j - i) % mod * calc_iphi(k)) % mod;
	}
	return ret;
}
int main()
{
	f[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				f[i * prime[j]] = f[i] * prime[j];
				break;
			}
			else
				f[i * prime[j]] = f[i] * (prime[j] - 1);
		f[i] = (f[i - 1] + (LL)i * f[i]) % mod;
	}
	for(LL n; scanf("%lld", &n) == 1; )
	{
		int ans = (LL)calc(n) * inv2 % mod;
		printf("%d\n", ans);
	}
	return 0;
}
