#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxm = 10001, maxn = 100000001, maxc = 9;
int tot, prime[maxm >> 3], d[maxm];
bool vis[maxn];
inline int mod_pow(int x, int k, int p)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline int mod_inv(int x, int p)
{
	int a, b;
	exgcd(x, p, a, b);
	return a < 0 ? a + p : a;
}
int main()
{
	vis[1] = 1;
	for(int i = 2; i < maxm; ++i)
	{
		if(!d[i])
		{
			prime[tot++] = d[i] = i;
			for(int j = i + i; j < maxn; j += i)
				vis[j] = 1;
		}
		for(int j = 0, k = (maxm - 1) / i; prime[j] <= k; ++j)
		{
			int o = i * prime[j];
			d[o] = prime[j];
			if(d[i] == prime[j])
				break;
		}
	}
	LL n;
	int lim;
	while(scanf("%lld%d", &n, &lim) == 2)
	{
		long long ans = 2 <= lim ? ((n + 1) >> 1) << 1 : 0; // p = 2
		for(int mod = 3; mod <= lim; ++mod)
		{
			if(vis[mod])
				continue;
			int c = 0, p[maxc] = {}, gen;
			{ // decomposition
				int tmp = mod - 1;
				for(int i = 0; tmp >= maxm && i < tot && prime[i] * prime[i] <= tmp; ++i)
					if(tmp % prime[i] == 0)
					{
						for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
						p[c++] = prime[i];
					}
				if(tmp >= maxm)
					p[c++] = tmp;
				else
					for(int pr = d[tmp]; pr; pr = d[tmp])
					{
						for(tmp /= pr; tmp % pr == 0; tmp /= pr);
						p[c++] = pr;
					}
			}
			for(gen = 2; ; ++gen)
			{
				bool flag = mod_pow(gen, mod - 1, mod) == 1;
				for(int i = 0; i < c && flag; ++i)
					flag &= mod_pow(gen, (mod - 1) / p[i], mod) != 1;
				if(flag)
					break;
			}
			int r = (mod - 1) >> 1, m = mod - 1;
			{ // 15x = r (mod m)
				int g = std::__gcd(15, r);
				m /= g;
				r = (LL)r * mod_inv(15 / g, m) % m;
			}
			int val = mod_pow(gen, r, mod), dt = mod_pow(gen, m, mod);
			for( ; r < mod - 1; r += m, val = (LL)val * dt % mod)
				if(n >= val)
					ans += mod * ((n - val) / mod + 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
