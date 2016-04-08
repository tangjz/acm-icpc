#include <cstdio>
typedef long long LL;
const int maxk = 11, maxs = 100001;
int t, k, prime, fact[maxs], inv[maxs];
LL n, m, ans, mod;
LL mod_add(LL x, LL y, LL p)
{
	LL ret = x + y;
	if(ret >= p)
		ret -= p;
	return ret;
}
LL mod_mul(LL x, LL y, LL p)
{
	LL ret = 0;
	while(y)
	{
		if(y & 1)
			ret = mod_add(ret, x, p);
		x = mod_add(x, x, p);
		y >>= 1;
	}
	return ret;
}
void exgcd(LL a, LL b, LL &x, LL &y)
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
void crt(LL &r, LL &m, LL r2, LL m2)
{
	LL r1 = r, m1 = m, x, y;
	exgcd(m1, m2, x, y); //(m1, m2) = 1
	if(x < 0)
		x += m2;
	x = mod_mul(x, r2 - r1 % m2 + m2, m2);
	r = x * m1 + r1;
	m = m1 * m2;
}
int C(LL n, LL m)
{
	if(n < m)
		return 0;
	if(n >= prime)
		return (LL)C(n / prime, m / prime) * C(n % prime, m % prime) % prime;
	return (LL)fact[n] * inv[fact[m]] % prime * inv[fact[n - m]] % prime;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%I64d%I64d%d", &n, &m, &k);
		ans = 0, mod = 1;
		for(int i = 0; i < k; ++i)
		{
			scanf("%d", &prime);
			fact[0] = 1;
			for(int j = 1; j < prime; ++j)
				fact[j] = (LL)fact[j - 1] * j % prime;
			inv[1] = 1;
			for(int j = 2; j < prime; ++j)
				inv[j] = prime - (LL)prime / j * inv[prime % j] % prime;
			crt(ans, mod, C(n, m), prime);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
