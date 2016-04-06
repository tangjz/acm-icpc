#include <cstdio>
#include <algorithm>
using namespace std;
const int maxm = 301, maxl = 1001;
typedef long long LL;
inline LL mod_add(LL x, LL y, LL p)
{
	return x + y >= p ? x + y - p : x + y;
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
inline LL mod_sqr(LL x, LL p)
{
	return mod_mul(x, x, p);
}
LL mod_pow(LL x, LL k, LL p)
{
	LL ret = 1;
	while(k)
	{
		if(k & 1)
			ret = mod_mul(ret, x, p);
		x = mod_mul(x, x, p);
		k >>= 1;
	}
	return ret;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % p;
		x = (LL)x * x % p;
		k >>= 1;
	}
	return ret;
}
int phi[maxn], fib_len[maxn], fib[maxn][maxl];
int calc_h(LL m, LL n, int p)
{
	return p == 1 ? 0 : mod_pow(fib[p][m % fib_len[p]], calc_h(m, n - 1, phi[p]), p);
}
int main()
{
	for(int i = 1; i < maxm; ++i)
	{
		int pre = 0, cur = 1 % i;
		do
		{
			++fib_len[i];
			pre = (pre + cur) % i;
			swap(pre, cur);
		} while(!(pre == 0 && cur == 1 % i));
	}
	int a, b, n, m, q;
	LL p, c, d, M, x;
	while(scanf("%d%d%d%lld%lld%lld%d%d%lld", &a, &b, &n, &p, &c, &d, &m, &q, &M) == 9)
		if(mod_pow(a, p - 1 >> 1, p) == p - 1 || mod_pow(b, p - 1 >> 1, p) == p - 1)
			puts("0");
		else
		{
			for(x = 1; d--; x *= c);
			printf("%lld\n", mod_sqr(mod_mul(calc_h(x, m, q), calc_g(a, b, n, p), M), M));
		}
	return 0;
}
