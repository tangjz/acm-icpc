#include <stdio.h>
#include <string.h>
typedef long long LL;
const LL mod = 119 * (1 << 23) + 1;
const int maxn = (1 << 15) + 1;
int tot;
LL a[maxn], b[maxn], c[maxn];
LL eps[maxn], inv_eps[maxn];
LL mod_pow(LL x, LL p)
{
	LL v = 1;
	while(p)
	{
		if(p & 1) v = x * v % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return v;
}
void init_eps(int n)
{
	tot = n;
	LL base = mod_pow(3, (mod - 1) / n);
	LL inv_base = mod_pow(base, mod - 2);
	eps[0] = 1, inv_eps[0] = 1;
	for(int i = 1; i < n; ++i)
	{
		eps[i] = eps[i - 1] * base % mod;
		inv_eps[i] = inv_eps[i - 1] * inv_base % mod;
	}
}
LL mod_add(LL x, LL d) 
{
	x += d; 
	return x >= mod ? x - mod : x; 
}
LL mod_sub(LL x, LL d) 
{
	x -= d; 
	return x < 0 ? x + mod : x; 
}
void NTT(int n, LL *x, LL *w)
{
	for(int i = 0, j = 0; i < n; ++i)
	{
		if(i > j) x[i] += x[j], x[j] = x[i] - x[j], x[i] -= x[j];
		for(int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	for(int i = 2; i <= n; i <<= 1)
		for(int j = 0, m = i >> 1; j < n; j += i)
			for(int k = 0; k < m; ++k)
			{
				LL z = x[j + m + k] * w[tot / i * k] % mod;
				x[j + m + k] = mod_sub(x[j + k], z);
				x[j + k] = mod_add(x[j + k], z);
			}
}
int n, m;
char s[maxn], t[maxn];
int main()
{
	init_eps(1 << 15);
	while(scanf("%s%s", s, t) == 2)
	{
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		n = strlen(s);
		for(int i = 0; i < n; ++i)
			a[i] = s[n - 1 - i] - '0';
		m = strlen(t);
		for(int i = 0; i < m; ++i)
			b[i] = t[m - 1 - i] - '0';
		n = (n < m ? m : n) << 1;
		for(int lbt = n & -n; lbt < n; n -= lbt, lbt = n & -n);
		n <<= 1;
		NTT(n, a, eps);
		NTT(n, b, eps);
		for(int i = 0; i < n; ++i)
			a[i] = a[i] * b[i] % mod;
		NTT(n, a, inv_eps);
		LL inv = mod_pow(n, mod - 2);
		for(int i = 0; i < n; ++i)
			a[i] = a[i] * inv % mod;
		for(int i = 0; i < n; ++i)
			if(a[i] >= 8)
			{
				a[i + 1] += a[i] >> 3;
				a[i] &= 7;
			}
		for( ; a[n]; ++n)
			if(a[n] >= 8)
			{
				a[n + 1] += a[n] >> 3;
				a[n] &= 7;
			}
		for( ; n > 1 && !a[n - 1]; --n);
		for(int i = n - 1; i >= 0; --i)
			putchar('0' + a[i]);
		putchar('\n');
	}
	return 0;
}
