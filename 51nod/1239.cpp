#include <map>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 4641589, mod = 1000000007, inv2 = 500000004;
map<LL, int> Hash;
int tot, prime[maxn], f[maxn];
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
int calc(LL x)
{
	if(x < maxn)
		return f[x];
	if(Hash.count(x))
		return Hash[x];
	int ret = x % mod * ((x + 1) % mod) % mod * inv2 % mod;
	for(LL i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		dec(ret, (j - i + 1) % mod * calc(x / i) % mod);
	}
	return Hash[x] = ret;
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
		inc(f[i], f[i - 1]);
	}
	LL n;
	scanf("%lld", &n);
	printf("%d\n", calc(n));
	return 0;
}
