#include <cstdio>
typedef long long LL;
const int maxm = 500002, mod = 1000000007;
int n, m, tot, prime[maxm], f[maxm], iact[maxm], invm, factm1, pre[maxm], suf[maxm], g0, a[maxm], b[maxm], ans;
int inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)inv(mod % x) % mod;
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
	scanf("%d%d", &n, &m);
	if(m == 1)
	{
		ans = (LL)n * (n + 1) % mod * inv(2) % mod;
		printf("%d\n", ans);
		return 0;
	}
	f[1] = 1;
	for(int i = 2; i <= m + 1; ++i)
	{
		if(!f[i])
		{
			prime[tot++] = i;
			f[i] = mod_pow(i, m);
		}
		for(int j = 0; j < tot && prime[j] <= (m + 1) / i; ++j)
		{
			f[i * prime[j]] = (LL)f[i] * f[prime[j]] % mod;
			if(i % prime[j] == 0)
				break;
		}
	}
	if(n <= m)
	{
		for(int i = 1, o = m; i <= n; ++i)
		{
			ans += (LL)f[i] * o % mod;
			if(ans >= mod)
				ans -= mod;
			o = (LL)o * m % mod;
		}
		printf("%d\n", ans);
		return 0;
	}
	iact[1] = 1;
	for(int i = 2; i <= m + 1; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	invm = iact[m];
	iact[0] = 1;
	for(int i = 1; i <= m + 1; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	factm1 = inv(iact[m + 1]);
	int A = 1, B = 0;
	a[0] = 1;
	for(int i = 1, o = 1; i <= m + 1; ++i)
	{
		int tmp = (LL)factm1 * iact[m - i + 1] % mod * iact[i] % mod;
		if(i & 1)
			tmp = mod - tmp;
		a[i] = (LL)a[i - 1] * invm % mod;
		b[i] = ((LL)b[i - 1] * invm + f[i]) % mod;
		A = (A + (LL)tmp * a[i]) % mod;
		B = (B + (LL)tmp * b[i]) % mod;
	}
	g0 = (LL)(mod - B) * inv(A) % mod;
	pre[0] = n;
	for(int i = 1; i <= m; ++i)
		pre[i] = (LL)pre[i - 1] * (n - i) % mod;
	suf[m] = n - m;
	for(int i = m - 1; i >= 0; --i)
		suf[i] = (LL)suf[i + 1] * (n - i) % mod;
	for(int i = 0; i <= m; ++i)
	{
		int tmp = ((LL)a[i] * g0 + b[i]) % mod;
		tmp = (LL)tmp * iact[i] % mod * iact[m - i] % mod;
		if(i)
			tmp = (LL)tmp * pre[i - 1] % mod;
		if(i < m)
			tmp = (LL)tmp * suf[i + 1] % mod;
		if(((m - i) & 1) && tmp)
			tmp = mod - tmp;
		ans += tmp;
		if(ans >= mod)
			ans -= mod;
	}
	ans = ((LL)mod_pow(m, n) * ans - g0) % mod;
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
