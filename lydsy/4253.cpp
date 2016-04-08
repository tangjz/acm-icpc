#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 16, maxm = 1 << 16, maxt = 10;
int cnt, sum;
LL n, pp[maxs], sei[maxs], ans[maxm];
LL gcd(LL a, LL b)
{
	return b ? gcd(b, a % b) : a;
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
bool miller_rabin(LL n)
{
	if(n == 2)
		return 1;
	if(n < 2 || !(n & 1))
		return 0;
	LL s = 0, r = n - 1;
	for( ; !(r & 1); r >>= 1)
		++s;
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
		r = gcd(abs(y - x), n);
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
			if(pp[i] % n == 0)
			{
				pp[i] *= n;
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

void dfs(int dep, LL now)
{
	if(dep == cnt)
	{
		ans[sum++] = now;
		return;
	}
	dfs(dep + 1, mod_add(now, sei[dep], n));
	if(pp[dep] != 2)
		dfs(dep + 1, mod_add(now, mod_mul(pp[dep] - 1, sei[dep], n), n));
	if(!(pp[dep] & 1) && pp[dep] > 4)
	{
		dfs(dep + 1, mod_add(now, mod_mul((pp[dep] >> 1) + 1, sei[dep], n), n));
		dfs(dep + 1, mod_add(now, mod_mul((pp[dep] >> 1) - 1, sei[dep], n), n));
	}
}
int main()
{
	scanf("%lld", &n);
	if(n == 1)
	{
		puts("None");
		return 0;
	}
	decomposition(n);
	for(int i = 0; i < cnt; ++i)
	{
		LL tmp, x, y;
		exgcd(n / pp[i], pp[i], x, y);
		if(x < 0)
			x += pp[i];
		sei[i] = mod_mul(x, n / pp[i], n);
	}
	dfs(0, 0);
	sort(ans, ans + sum);
	for(int i = 0; i < sum; ++i)
		printf("%lld%c", ans[i], " \n"[i == sum - 1]);
	return 0;
}
