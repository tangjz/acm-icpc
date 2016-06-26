#include <cstdio>
typedef long long LL;
const int maxn = 1000001;
int n, p, fact[maxn], iact[maxn], f[maxn], sz[maxn];
int C(int n, int m)
{
	if(n < m)
		return 0;
	if(n >= p)
		return (LL)C(n / p, m / p) * C(n % p, m % p) % p;
	return (LL)fact[n] * iact[m] % p * iact[n - m] % p;
}
int main()
{
	scanf("%d%d", &n, &p);
	int lim = n < p ? n : p;
	iact[1] = 1;
	for(int i = 2; i < lim; ++i)
		iact[i] = p - p / i * (LL)iact[p % i] % p;
	fact[0] = iact[0] = 1;
	for(int i = 1; i < lim; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % p;
		iact[i] = (LL)iact[i - 1] * iact[i] % p;
	}
	for(int i = n; i > n >> 1; --i)
		f[i] = sz[i] = 1;
	for(int i = n >> 1; i; --i)
	{
		f[i] = (LL)C(sz[i << 1] + sz[i << 1 | 1], sz[i << 1]) * f[i << 1] % p * ((i << 1 | 1) <= n ? f[i << 1 | 1] : 1) % p;
		sz[i] = sz[i << 1] + sz[i << 1 | 1] + 1;
	}
	printf("%d\n", f[1]);
	return 0;
}
