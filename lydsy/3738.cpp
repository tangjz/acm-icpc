#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 20;
int p, nk, pp, prod, ans, mod, f[maxn], g[maxn], h[maxn];
inline int mod_add(int x, int y)
{
	return x + y >= pp ? x + y - pp : x + y;
}
inline int mod_sub(int x, int y)
{
	return x - y < 0 ? x - y + pp : x - y;
}
inline int mod_mul(int x, int y)
{
	return (LL)x * y % pp;
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
int mod_inv(int x)
{
	int tmpx, tmpy;
	exgcd(x, pp, tmpx, tmpy); //(x, pp) = 1
	if(tmpx < 0)
		tmpx += pp;
	return tmpx;
}
int mod_pow(int x, LL k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = mod_mul(ret, x);
		x = mod_mul(x, x);
		k >>= 1;
	}
	return ret;
}
void CRT(int r2)
{
	int &r = ans, &m = mod, r1 = ans, m1 = mod, m2 = pp, x, y;
	exgcd(m1, m2, x, y); //(m1, m2) = 1
	if(x < 0)
		x += m2;
	x = mod_mul(x, r2 - r1 % m2 + m2);
	r = x * m1 + r1;
	m = m1 * m2;
}
void calc(int x)
{
	if(!x)
	{
		memset(f, 0, nk * sizeof(int));
		f[0] = 1;
		return;
	}
	int xx = x / 2 / p * p; // xx = 0 + pk
	// f = calc[0, xx)
	calc(xx);
	//g = calc[xx, xx * 2) = f(x + xx)
	memset(g, 0, nk * sizeof(int));
	memset(h, 0, nk * sizeof(int));
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
	// f = calc[0, xx * 2)
	memcpy(h, f, nk * sizeof(int));
	for(int i = 0; i < nk; ++i)
	{
		LL tmp = 0;
		for(int j = 0; j <= i; ++j)
			tmp += mod_mul(g[j], h[i - j]);
		f[i] = tmp % pp;
	}
	// f = calc[0, x)
	for(int i = xx << 1; i < x; ++i)
	{
		if(i % p == 0)
			continue;
		for(int j = nk - 1; j >= 0; --j)
		{
			f[j] = mod_mul(f[j], i);
			if(j > 0)
				f[j] = mod_add(f[j - 1], f[j]);
		}
	}
}
pair<int, LL> mod_fact(LL n)
{
	if(n == 0)
		return make_pair(1, 0);
	pair<int, LL> ret = mod_fact(n / p);
	ret.second += n / p;
	if(n >= pp)
	{
		ret.first = mod_mul(ret.first, mod_pow(prod, n / pp));
		n %= pp;
	}
	calc(n + 1);
	ret.first = mod_mul(ret.first, f[0]);
	return ret;
}
LL N, M;
pair<int, LL> all, now;
void solve() // (n + m)! / n! / m!
{
	all = make_pair(1, 0);
	now = mod_fact(N + M);
	all.first = mod_mul(all.first, now.first);
	all.second += now.second;
	now = mod_fact(N);
	all.first = mod_mul(all.first, mod_inv(now.first));
	all.second -= now.second;
	now = mod_fact(M);
	all.first = mod_mul(all.first, mod_inv(now.first));
	all.second -= now.second;
}
void check()
{
	int ret = 0;
	if(all.second < nk)
	{
		ret = all.first;
		for(int i = 0; i < all.second; ++i)
			ret = mod_mul(ret, p);
	}
	CRT(ret);
}
int main()
{
	while(scanf("%lld%lld%d", &M, &N, &nk) == 3)
	{
		ans = 0, mod = 1;
		p = 2, pp = 1;
		for(int i = 0; i < nk; ++i)
			pp *= p;
		calc(pp);
		prod = f[0];
		solve();
		int lastp = p, lastpp = pp;
		pair<int, LL> lastall = all;
		p = 5, pp = 1;
		for(int i = 0; i < nk; ++i)
			pp *= p;
		calc(pp);
		prod = f[0];
		solve();
		LL exp = min(lastall.second, all.second);
		all.first = mod_mul(all.first, mod_inv(mod_pow(lastp, exp)));
		all.second -= exp;
		check();
		swap(p, lastp);
		swap(pp, lastpp);
		swap(all, lastall);
		all.first = mod_mul(all.first, mod_inv(mod_pow(lastp, exp)));
		all.second -= exp;
		check();
		printf("%0*d\n", nk, ans);
	}
	return 0;
}
