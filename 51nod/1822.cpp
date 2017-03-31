#include <stdio.h>
#include <cstring>
// #include <cassert>
typedef long long LL;
const int maxm = 200002, mod = 985661441;
int t, m, iact[maxm], tot, prime[maxm >> 3], f[maxm], g[maxm], h[maxm];
LL n, r;
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
inline void sieve() // increse m by 1, then sieve primes in [1, m] and calculate f[i] = mod_pow(i, m - 1)
{
	++m;
	tot = 0;
	memset(f, 0, (m + 1) * sizeof(int)); // f[0] = 0;
	f[1] = 1;
	for(int i = 2; i <= m; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = mod_pow(i, m - 1);
		}
		for(int j = 0, k = m / i; j < tot && prime[j] <= k; ++j)
		{
			f[i * prime[j]] = (LL)f[i] * f[prime[j]] % mod;
			if(i % prime[j] == 0)
				break;
		}
	}
}
inline int value() // calculate f(n) when f(0), f(1), ..., f(m) is given, where m is the degree of f(x)
{
	int ret = 0;
	static int *pre = g, *suf = h;
	pre[0] = n % mod;
	for(int i = 1; i <= m; ++i)
		pre[i] = (n - i) % mod * pre[i - 1] % mod;
	suf[m] = (n - m) % mod;
	for(int i = m - 1; i >= 0; --i)
		suf[i] = (n - i) % mod * suf[i + 1] % mod;
	for(int i = 0; i <= m; ++i)
	{
		int tmp = (LL)f[i] * iact[i] % mod * iact[m - i] % mod;
		if(i)
			tmp = (LL)tmp * pre[i - 1] % mod;
		if(i < m)
			tmp = (LL)tmp * suf[i + 1] % mod;
		if(((m - i) & 1) && tmp)
			tmp = mod - tmp;
		if((ret += tmp) >= mod)
			ret -= mod;
	}
	return ret;
}
inline int solve1()
{
	for(int i = 2; i <= m; ++i)
		if((f[i] += f[i - 1]) >= mod)
			f[i] -= mod;
	return n <= m ? f[(int)n] : value();
}
inline int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int solve2()
{
	int ret = 0;
	if(n <= m)
	{
		for(int i = 1, o = r; i <= n; ++i, o = (LL)o * r % mod)
			ret = (ret + (LL)f[i] * o) % mod;
		return ret;
	}
	int invr = mod_inv(r), factm1 = mod_inv(iact[m]), sA = 1, sB = 0;
	static int *a = g, *b = h;
	a[0] = 1, b[0] = 0;
	for(int i = 1; i <= m; ++i)
	{
		int tmp = (LL)factm1 * iact[m - i] % mod * iact[i] % mod;
		if((i & 1) && tmp)
			tmp = mod - tmp;
		a[i] = (LL)a[i - 1] * invr % mod;
		b[i] = ((LL)b[i - 1] * invr + f[i]) % mod;
		sA = (sA + (LL)tmp * a[i]) % mod;
		sB = (sB + (LL)tmp * b[i]) % mod;
	}
	f[0] = (LL)(mod - sB) * mod_inv(sA) % mod; // sA = (1 - R^(m+1)) / (R^m - R^(m+1)) != 0
	--m;
	for(int i = 1; i <= m; ++i)
		f[i] = ((LL)a[i] * f[0] + b[i]) % mod;
	ret = value();
	if((ret = ((LL)mod_pow(r, n % (mod - 1)) * ret - f[0]) % mod) < 0)
		ret += mod;
	return ret;
}
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxm; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	/*assert(*/scanf("%d", &t)/* == 1 && 1 <= t && t <= 500)*/;
	while(t--)
	{
		/*static int sum_m = 0;
		assert(*/scanf("%d%lld%lld", &m, &n, &r)/* == 3
		&& 1 <= m && m <= 200000
		&& (sum_m += m) <= 10000000
		&& 1 <= n && n <= (LL)1e18
		&& 1 <= r && r <= (LL)1e18)*/;
		sieve();
		printf("%d\n", (r %= mod) == 1 ? solve1() : solve2());
	}
	return 0;
}
