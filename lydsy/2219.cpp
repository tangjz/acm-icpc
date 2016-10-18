#include <map>
#include <cmath>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 31623, maxs = 10;
int mod_pow(int x, int k, int p)
{
	int ret = 1; // p > 1
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
void exgcd(int a, int b, int &x, int &y)
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
int mod_inv(int x, int p)
{
	int ret, tmp;
	exgcd(x, p, ret, tmp);
	return ret < 0 ? ret + p : ret;
}
std::map<int, int> Hash;
int bsgs(int pp, int x, int y) // x^k = y (mod pp)
{
	int sz = (int)ceil(sqrt(pp)), lim = (pp - 1) / sz + 1;
	std::map<int, int>().swap(Hash);
	for(int i = 0, j = 1; i < sz; ++i, j = (LL)j * x % pp)
		if(!Hash.count(j))
			Hash[j] = i;
	int inver = mod_inv(mod_pow(x, sz, pp), pp);
	for(int i = 0, j = y; i < lim; ++i, j = (LL)j * inver % pp)
		if(Hash.count(j))
			return i * sz + Hash[j];
	return -1;
}
int tot, prime[maxn];
bool vis[maxn];
int prim_root(int mod)
{
	int tmp = mod - 1, c = 0;
	static int p[maxs];
	for(int i = 0; i < tot && prime[i] * prime[i] <= tmp; ++i)
	{
		if(tmp % prime[i])
			continue;
		for(tmp /= prime[i]; tmp % prime[i] == 0; tmp /= prime[i]);
		p[c++] = prime[i];
	}
	if(tmp > 1)
		p[c++] = tmp;
	for(int g = 2; ; ++g)
	{
		bool flag = mod_pow(g, mod - 1, mod) == 1;
		for(int i = 0; i < c && flag; ++i)
			flag &= mod_pow(g, (mod - 1) / p[i], mod) != 1;
		if(flag)
			return g;
	}
}
int solve(int p, int e, int k, int y) // x^k = y (mod p^e)
{
	int mod = 1;
	for(int i = 0; i < e; ++i)
		mod *= p;
	int r = std::__gcd(mod, y %= mod), ret = 1;
	if(!y)
	{
		for(int i = (e - 1) / k + 1; i < e; ++i)
			ret *= p;
		return ret;
	}
	else if(r > 1)
	{
		int cnt = 0;
		for( ; y % p == 0; ++cnt, y /= p, mod /= p);
		if(cnt % k)
			return 0;
		for(int i = cnt / k; i < cnt; ++i)
			ret *= p;
	}
	int g = prim_root(p), id = bsgs(mod, g, y);
	mod -= mod / p;
	r = std::__gcd(k, mod);
	if(id == -1 || id % r)
		return 0;
	return ret * r;
}
int t, a, b, m, c, p[maxs], e[maxs];
int main()
{
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxn; ++i)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &a, &b, &m);
		m = m << 1 | 1;
		c = 0;
		for(int i = 0; i < tot && prime[i] * prime[i] <= m; ++i)
		{
			if(m % prime[i])
				continue;
			for(e[c] = 1, m /= prime[i]; m % prime[i] == 0; ++e[c], m /= prime[i]);
			p[c++] = prime[i];
		}
		if(m > 1)
		{
			p[c] = m;
			e[c++] = 1;
		}
		int ans = 1;
		for(int i = 0; i < c; ++i)
			ans *= solve(p[i], e[i], a, b);
		printf("%d\n", ans);
	}
	return 0;
}
