#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 4641589, mod = 1000000007, inv2 = 500000004;
map<LL, int> Hash1, Hash2;
int tot, prime[maxn], f[maxn], g[maxn], ans;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
int calc_mu(LL x)
{
	if(x < maxn)
		return f[x];
	if(Hash1.count(x))
		return Hash1[x];
	int ret = 1;
	for(LL i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (j - i + 1) % mod * calc_mu(x / i) % mod);
	}
	return Hash1[x] = ret;
}
int calc_mu(LL L, LL R)
{
	int ret = calc_mu(R);
	dec(ret, calc_mu(L - 1));
	return ret;
}
int calc_phi(LL x)
{
	if(x < maxn)
		return g[x];
	if(Hash2.count(x))
		return Hash2[x];
	int ret = 0;
	for(LL i = 1, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		inc(ret, (x / i % mod) * ((x / i + 1) % mod) % mod * inv2 % mod * calc_mu(i, j) % mod);
	}
	return ret;
}
int calc_phi(LL L, LL R)
{
	int ret = calc_phi(R);
	dec(ret, calc_phi(L - 1));
	return ret;
}
int main()
{
	f[1] = g[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!g[i])
		{
			prime[tot++] = i;
			dec(f[i], 1);
			g[i] = i - 1;
		}
		for(int j = 0, k = (maxn - 1) / i; j < tot && prime[j] <= k; ++j)
			if(i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] * prime[j];
				break;
			}
			else
			{
				dec(f[i * prime[j]], f[i]);
				g[i * prime[j]] = g[i] * (prime[j] - 1);
			}
		inc(f[i], f[i - 1]);
		inc(g[i], g[i - 1]);
	}
	LL n;
	scanf("%lld", &n);
	for(LL i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		inc(ans, (n / i % mod) * (n / i % mod) % mod * calc_phi(i, j) % mod);
	}
	printf("%d\n", ans);
	return 0;
}
