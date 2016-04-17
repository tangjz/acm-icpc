#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define v first
#define e second
typedef long long LL;
typedef long double DB;
const int maxn = 20;
int p, nk;
LL pp, prod, ans, mod, f[maxn], g[maxn], h[maxn];
inline LL mod_add(LL x, LL y)
{
	return x + y >= pp ? x + y - pp : x + y;
}
inline LL mod_sub(LL x, LL y)
{
	return x - y < 0 ? x - y + pp : x - y;
}
inline LL mod_mul(LL x, LL y)
{
	LL ret = x * y - (LL)((DB)x * y / pp + 0.01) * pp;
	return ret < 0 ? ret + pp : ret;
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
inline LL mod_inv(LL x)
{
	LL tmpx, tmpy;
	exgcd(x, pp, tmpx, tmpy);
	return tmpx < 0 ? tmpx + pp : tmpx;
}
LL mod_pow(LL x, LL k)
{
	LL ret = 1;
	for( ; k; k >>= 1, x = mod_mul(x, x))
		if(k & 1)
			ret = mod_mul(ret, x);
	return ret;
}
void CRT(LL r2)
{
	LL x, y;
	exgcd(mod, pp, x, y);
	x = mod_mul(x < 0 ? x + pp : x, r2 - ans % pp + pp);
	ans += x * mod;
	mod *= pp;
}
void calc(LL x)
{
	if(!x)
	{
		memset(f, 0, nk * sizeof(LL));
		f[0] = 1;
		return;
	}
	LL xx = x / 2 / p * p;
	calc(xx);
	memset(g, 0, nk * sizeof(LL));
	memset(h, 0, nk * sizeof(LL));
	h[0] = 1;
	for(int i = 0; i < nk; ++i)
	{
		for(int j = 0; j < nk; ++j)
			g[j] = mod_add(g[j], mod_mul(f[i], h[j]));
		if(i == nk - 1)
			break;
		for(int j = nk - 1; j >= 0; --j)
		{
			h[j] = mod_mul(h[j], xx);
			if(j)
				h[j] = mod_add(h[j - 1], h[j]);
		}
	}
	memcpy(h, f, nk * sizeof(LL));
	for(int i = 0; i < nk; ++i)
	{
		LL tmp = 0;
		for(int j = 0; j <= i; ++j)
			tmp += mod_mul(g[j], h[i - j]);
		f[i] = tmp % pp;
	}
	for(LL i = xx << 1; i < x; ++i)
	{
		if(i % p == 0)
			continue;
		for(int j = nk - 1; j >= 0; --j)
		{
			f[j] = mod_mul(f[j], i);
			if(j)
				f[j] = mod_add(f[j - 1], f[j]);
		}
	}
}
pair<LL, LL> mod_fact(LL n)
{
	if(n == 0)
		return {1, 0};
	pair<LL, LL> ret = mod_fact(n / p);
	ret.e += n / p;
	if(n >= pp)
	{
		ret.v = mod_mul(ret.v, mod_pow(prod, n / pp));
		n %= pp;
	}
	calc(n + 1);
	ret.v = mod_mul(ret.v, f[0]);
	return ret;
}
LL N, M;
pair<LL, LL> all, now;
void solve()
{
	all = {1, 0};
	now = mod_fact(N + M);
	all.v = mod_mul(all.v, now.v);
	all.e += now.e;
	now = mod_fact(N);
	all.v = mod_mul(all.v, mod_inv(now.v));
	all.e -= now.e;
	now = mod_fact(M);
	all.v = mod_mul(all.v, mod_inv(now.v));
	all.e -= now.e;
}
void check()
{
	LL ret = 0;
	if(all.e < nk)
	{
		ret = all.v;
		for(int i = 0; i < all.e; ++i)
			ret = mod_mul(ret, p);
	}
	CRT(ret);
}
int main()
{
	scanf("%lld%lld%d", &M, &N, &nk);
	ans = 0, mod = 1;
	p = 2, pp = 1;
	for(int i = 0; i < nk; ++i)
		pp *= p;
	calc(pp);
	prod = f[0];
	solve();
	int lastp = p;
	LL lastpp = pp;
	pair<LL, LL> lastall = all;
	p = 5, pp = 1;
	for(int i = 0; i < nk; ++i)
		pp *= p;
	calc(pp);
	prod = f[0];
	solve();
	LL exp = min(lastall.e, all.e);
	all.v = mod_mul(all.v, mod_inv(mod_pow(lastp, exp)));
	all.e -= exp;
	check();
	swap(p, lastp);
	swap(pp, lastpp);
	swap(all, lastall);
	all.v = mod_mul(all.v, mod_inv(mod_pow(lastp, exp)));
	all.e -= exp;
	check();
	printf("%0*lld\n", nk, ans);
	return 0;
}
