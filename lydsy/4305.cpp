#include <cstdio>
typedef long long LL;
const int maxn = 300001, mod = 1000000007;
int n, m, p, mx, c[maxn], fact[maxn], inv[maxn], f[maxn];
int mod_binom(int n, int m)
{
	return n < m ? 0 : (LL)fact[n] * inv[m] % mod * inv[n - m] % mod;
}
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
	scanf("%d%d%d", &n, &m, &p);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	fact[0] = inv[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	}
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		++c[x];
		if(mx < x)
			mx = x;
	}
	for(int i = 1; i <= mx; ++i)
		for(int j = i + i; j <= mx; j += i)
			c[i] += c[j];
	for(int i = mx; i >= 1; --i)
	{
		f[i] = c[i] < n - p ? 0 : (LL)mod_binom(c[i], n - p) * mod_pow(m / i - 1, c[i] - (n - p)) % mod * mod_pow(m / i, n - c[i]) % mod;
		for(int j = i + i; j <= mx; j += i)
		{
			f[i] -= f[j];
			if(f[i] < 0)
				f[i] += mod;
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d%c", f[i], " \n"[i == m]);
	return 0;
}
