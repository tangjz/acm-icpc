#include <stdio.h>
#include <string.h>
typedef long long LL;
const LL mod = 119 * (1 << 23) + 1;
const int maxn = (1 << 18) + 1;
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
void poly_inv(int deg, LL* a, LL* b, LL* tmp)
{
	if(deg == 1)
	{
		b[0] = mod_pow(a[0], mod - 2);
		return;
	}
	poly_inv((deg + 1) >> 1, a, b, tmp);
	int p = 1;
	while(p < deg << 1) p <<= 1;
	memcpy(tmp, a, deg * sizeof(LL));
	memset(tmp + deg, 0, (p - deg) * sizeof(LL));
	NTT(p, tmp, eps);
	NTT(p, b, eps);
	for(int i = 0; i < p; ++i)
	{
		b[i] = (2 - tmp[i] * b[i] % mod) * b[i] % mod;
		if(b[i] < 0) b[i] += mod;
	}
	NTT(p, b, inv_eps);
	LL inv = mod_pow(p, mod - 2);
	for(int i = 0; i < p; ++i)
		b[i] = b[i] * inv % mod;
	memset(b + deg, 0, (p - deg) * sizeof(LL));
}
int main()
{
	init_eps(1 << 18);
	int n = 100001;
	a[0] = 1;
	for(int i = 1; i < n; ++i)
		a[i] = a[i - 1] * i % mod;
	poly_inv(n, a, b, c);
	for(int i = 1; i < n; ++i)
	{
		b[i] = -b[i] % mod;
		if(b[i] < 0) b[i] += mod;
	}
	int t, x;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &x);
		printf("%d\n", (int)b[x]);
	}
	return 0;
}
