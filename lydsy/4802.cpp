#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxs = 16, maxm = 1 << 16, maxt = 10;
int cnt, sum;
LL n, pp[maxs], sei[maxs], ans[maxm];
LL mod_add(LL x, LL y, LL p)
{
	return (x += y) < p ? x : x - p;
}
LL mod_mul(LL x, LL y, LL p)
{
	return (x = x * y - (LL)((DB)x * y / p + 0.001) * p) < 0 ? x + p : x;
}
LL mod_pow(LL x, LL k, LL p)
{
	LL ret = 1;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
		if(k & 1)
			ret = mod_mul(ret, x, p);
	return ret;
}
bool miller_rabin(LL n)
{
	if(n == 2)
		return 1;
	if(n < 2 || !(n & 1))
		return 0;
	LL s = 0, r = n - 1;
	for( ; !(r & 1); r >>= 1, ++s);
	for(int i = 0; i < maxt; ++i)
	{
		LL cur = mod_pow(rand() % (n - 2) + 2, r, n), nxt;
		for(int j = 0; j < s; ++j)
		{
			nxt = mod_mul(cur, cur, n);
			if(nxt == 1 && cur != 1 && cur != n - 1)
				return 0;
			cur = nxt;
		}
		if(cur != 1)
			return 0;
	}
	return 1;
}
LL pollard_rho(LL n)
{
	LL x = (LL)rand() * rand() % n, y = x, c = (LL)rand() * rand() % n, r;
	for(LL i = 1, k = 2; ; ++i)
	{
		if(i == k)
		{
			y = x;
			k <<= 1;
		}
		x = mod_add(mod_mul(x, x, n), c, n);
		r = __gcd(abs(y - x), n);
		if(r != 1)
			return r;
	}
}
void decomposition(LL n)
{
	if(miller_rabin(n))
	{
		bool flag = 0;
		for(int i = 0; i < cnt; ++i)
			if(n == pp[i])
			{
				flag = 1;
				break;
			}
		if(!flag)
			pp[cnt++] = n;
	}
	else
	{
		LL fact;
		while((fact = pollard_rho(n)) == n);
		decomposition(fact);
		decomposition(n / fact);
	}
}

int main()
{
	scanf("%lld", &n);
	if(n == 1)
	{
		puts("1");
		return 0;
	}
	decomposition(n);
	for(int i = 0; i < cnt; ++i)
		n -= n / pp[i];
	printf("%lld\n", n);
	return 0;
}
