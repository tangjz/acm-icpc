#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int ans, mod;
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
int mod_inv(int x, int pp)
{
	int tx, ty;
	exgcd(x, pp, tx, ty); //(x, pp) = 1
	if(tx < 0)
		tx += pp;
	return tx;
}
int mod_pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = ret * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ret;
}
void CRT(int r, int m)
{
	int x = (LL)mod_inv(mod, m) * (r - ans) % m;
	if(x < 0)
		x += m;
	ans += x * mod;
	mod *= m;
}
const int maxn = 8, maxp = 10202;
int n, n1, n2, m, a[maxn], fact[maxp];
pair<int, int> mod_fact(int n, int p, int pp)
{
	if(n == 0)
		return {1, 0};
	pair<int, int> ret = mod_fact(n / p, p, pp);
	ret.second += n / p;
	if(n >= pp)
	{
		ret.first = ret.first * mod_pow(fact[pp - 1], n / pp, pp) % pp;
		n %= pp;
	}
	ret.first = ret.first * fact[n] % pp;
	return ret;
}
void solve(int p, int e, int pp)
{
	fact[0] = 1;
	for(int i = 1; i < pp; ++i)
		fact[i] = i % p ? fact[i - 1] * i % pp : fact[i - 1];
	int ret = 0;
	for(int msk = 0, all = 1 << n1; msk < all; ++msk)
	{
		int flag = 1, res = m;
		for(int i = 0; i < n1; ++i)
			if((msk >> i) & 1)
			{
				flag = -flag;
				res -= a[i];
			}
		if(res < n)
			continue;
		pair<int, int> a = mod_fact(res - 1, p, pp);
		pair<int, int> b = mod_fact(res - n, p, pp);
		pair<int, int> c = mod_fact(n - 1, p, pp);
		int exp = a.second - b.second - c.second;
		if(exp > e)
			continue;
		int val = a.first * mod_inv(b.first, pp) % pp * mod_inv(c.first, pp) % pp;
		while(exp--)
			val = val * p % pp;
		if(flag == -1)
			val = pp - val;
		ret += val;
		if(ret >= pp)
			ret -= pp;
	}
	CRT(ret, pp);
}
const int maxs = 5;
int t, pr, tot, p[maxs], e[maxs], pp[maxs];
int main()
{
	scanf("%d%d", &t, &pr);
	for(int i = 2; i < maxp; ++i)
	{
		if(pr % i)
			continue;
		for(e[tot] = 0, pp[tot] = 1; pr % i == 0; ++e[tot], pp[tot] *= i, pr /= i);
		p[tot++] = i;
	}
	while(t--)
	{
		scanf("%d%d%d%d", &n, &n1, &n2, &m);
		for(int i = 0; i < n1; ++i)
			scanf("%d", a + i);
		while(n2--)
		{
			int x;
			scanf("%d", &x);
			m -= x - 1;
		}
		if(m < n)
		{
			puts("0");
			continue;
		}
		ans = 0;
		mod = 1;
		for(int i = 0; i < tot; ++i)
			solve(p[i], e[i], pp[i]);
		printf("%d\n", ans);
	}
	return 0;
}
