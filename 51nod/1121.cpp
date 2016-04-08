#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = 20;
int p, nk, n, sz;
LL pp, prod, ans, mod, f[maxn], g[maxn], h[maxn];
LL mod_add(LL x, LL y)
{
	x += y;
	if(x >= pp)
		x -= pp;
	return x;
}
LL mod_sub(LL x, LL y)
{
	x -= y;
	if(x < 0)
		x += pp;
	return x;
}
LL mod_mul(LL x, LL y)
{
	/*LL ret = 0;
	if(x < y)
		swap(x, y);
	while(y)
	{
		if(y & 1)
			ret = mod_add(ret, x);
		x = mod_add(x, x);
		y >>= 1;
	}*/
	LL ret = x * y - (LL)((DB)x * y / pp + 0.01) * pp;
	if(ret < 0)
		ret += pp;
	//LL ret = (__int128)x * y % pp;
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
LL mod_inv(LL x)
{
	LL tmpx, tmpy;
	exgcd(x, pp, tmpx, tmpy); //(x, pp) = 1
	if(tmpx < 0)
		tmpx += pp;
	return tmpx;
}
LL mod_pow(LL x, LL k)
{
	LL ret = 1;
	while(k)
	{
		if(k & 1)
			ret = mod_mul(ret, x);
		x = mod_mul(x, x);
		k >>= 1;
	}
	return ret;
}
void CRT(LL r2)
{
	LL &r = ans, &m = mod, r1 = ans, m1 = mod, m2 = pp, x, y;
	exgcd(m1, m2, x, y); //(m1, m2) = 1
	if(x < 0)
		x += m2;
	x = mod_mul(x, r2 - r1 % m2 + m2);
	r = x * m1 + r1;
	m = m1 * m2;
}
void calc(LL x)
{
	if(!x)
	{
		memset(f, 0, sizeof f);
		f[0] = 1;
		return;
	}
	LL xx = x / 2 / p * p; // xx = 0 + pk
	// f = calc[0, xx)
	calc(xx);
	//g = calc[xx, xx * 2) = f(x + xx)
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	h[0] = 1;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
			g[j] = mod_add(g[j], mod_mul(f[i], h[j]));
		if(i == n - 1)
			continue;
		for(int j = n - 1; j >= 0; --j)
		{
			h[j] = mod_mul(h[j], xx);
			if(j)
				h[j] = mod_add(h[j - 1], h[j]);
		}
	}
	// f = calc[0, xx * 2)
	memcpy(h, f, sizeof f);
	for(int i = 0; i < n; ++i)
	{
		LL tmp = 0;
		for(int j = 0; j <= i; ++j)
			tmp += mod_mul(g[j], h[i - j]);
		f[i] = tmp % pp;
	}
	// f = calc[0, x)
	for(LL i = xx << 1; i < x; ++i)
	{
		if(i % p == 0)
			continue;
		for(int j = n - 1; j >= 0; --j)
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
		return make_pair(1, 0);
	pair<LL, LL> ret = mod_fact(n / p);
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
pair<LL, LL> all, now;
void solve() // (n - m + 1) * (n + m)! / (n + 1)! / m!
{
	all = make_pair(1, 0);
	{
		LL tmp = N - M + 1;
		for( ; tmp % p == 0; tmp /= p)
			++all.second;
		all.first = mod_mul(all.first, tmp);
	}
	now = mod_fact(N + M);
	all.first = mod_mul(all.first, now.first);
	all.second += now.second;
	now = mod_fact(N + 1);
	all.first = mod_mul(all.first, mod_inv(now.first));
	all.second -= now.second;
	now = mod_fact(M);
	all.first = mod_mul(all.first, mod_inv(now.first));
	all.second -= now.second;
	LL ret = 0;
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
	while(scanf("%lld%lld", &M, &N) == 2)
	{
		ans = 0, mod = 1, nk = 18, n = 18;
		p = 2, pp = 262144, sz = 512;
		calc(pp);
		prod = f[0];
		solve();
		p = 5, pp = 3814697265625LL, sz = 1953125;
		calc(pp);
		prod = f[0];
		solve();
		printf("%lld\n", ans);
	}
	return 0;
}
