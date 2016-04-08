#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 4641589, mod = 1000000007, inv2 = 500000004, inv6 = 166666668;
map<LL, int> Hash2;
int tot, prime[maxn], g[maxn], ans;
inline void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
inline void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
inline int num1(LL x)
{
	x %= mod;
	return x * (x + 1) % mod * inv2 % mod;
}
inline int num1(LL L, LL R)
{
	int ret = num1(R);
	dec(ret, num1(L - 1));
	return ret;
}
inline int num2(LL x)
{
	x %= mod;
	return x * (x + 1) % mod * (x * 2 % mod + 1) % mod * inv6 % mod;
}
inline int num2(LL L, LL R)
{
	int ret = num2(R);
	dec(ret, num2(L - 1));
	return ret;
}
inline int num3(LL x)
{
	int ret = num1(x);
	return (LL)ret * ret % mod;
}
int calc_i2phi(LL x)
{
	if(x < maxn)
		return g[x];
	if(Hash2.count(x))
		return Hash2[x];
	int ret = num3(x);
	for(LL i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (LL)num2(i, j) * calc_i2phi(x / i) % mod);
	}
	return Hash2[x] = ret;
}
int main()
{
	g[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!g[i])
		{
			prime[tot++] = i;
			g[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] * prime[j];
				break;
			}
			else
				g[i * prime[j]] = g[i] * (prime[j] - 1);
		g[i] = (g[i - 1] + (LL)i * i % mod * g[i]) % mod;
	}
	LL n;
	scanf("%lld", &n);
	for(LL i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ans, num1(i, j) * (LL)calc_i2phi(n / i) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
