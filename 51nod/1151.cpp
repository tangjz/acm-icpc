#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxp = 5, maxn = 19, maxl = 61;
int p, sz;
LL pp, pw[maxn], c[maxn][maxn];
inline LL mod_add(LL x, LL y, LL m) { // (x + y) mod m
	return (x += y) >= m ? x - m : x;
}
inline LL mod_sub(LL x, LL y, LL m) { // (x - y) mod m
	return (x -= y) < 0 ? x + m : x;
}
inline LL mod_mul(LL x, LL y, LL m) { // (x * y) mod m
	return (__int128_t)x * y % m;
}
inline void exgcd(LL a, LL b, LL &x, LL &y) { // a x + b y = r
	if(!b) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline LL mod_inv(LL x, LL m) { // x^-1 mod m
	LL u, v;
	exgcd(x, m, u, v); //(x, m) = 1
	return u < 0 ? u + m : u;
}
inline LL mod_pow(LL x, LL k, LL m) { // x^k mod m
	LL ret = 1;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, m))
		if(k & 1)
			ret = mod_mul(ret, x, m);
	return ret;
}
LL ans, mod;
inline void CRT(LL r2) { // (ans, mod) x (r2, pp) -> (ans, mod)
	LL &r = ans, &m = mod, r1 = ans, m1 = mod, m2 = pp, x, y;
	exgcd(m1, m2, x, y); //(m1, m2) = 1
	x = x < 0 ? x + m2 : x;
	x = mod_mul(x, r2 - r1 % m2 + m2, m2);
	r = x * m1 + r1;
	m = m1 * m2;
}
LL s[maxp][maxn], f[maxn], g[3][maxn];
void poly_mul(LL f[], LL g[], LL h[]) { // h = f, f = g * h
	memcpy(h, f, sz * sizeof(LL));
	memset(f, 0, sz * sizeof(LL));
	for(int i = 0; i < sz; ++i) {
		if(!g[i])
			continue;
		for(int j = 0, k = i; k < sz; ++j, ++k) {
			if(!h[j])
				continue;
			f[k] = mod_add(f[k], mod_mul(g[i], h[j], pw[sz - k]), pw[sz - k]);
		}
	}
}
void poly_val(LL f[], LL x, LL g[], LL h[]) { // g(z) = f(z + x)
	memset(g, 0, sz * sizeof(LL));
	h[0] = 1;
	for(int i = 1; i < sz; ++i)
		h[i] = mod_mul(h[i - 1], x, pp);
	for(int i = 0; i < sz; ++i) {
		if(!f[i])
			continue;
		for(int j = 0; j <= i; ++j) {
			if(!c[i][j])
				continue;
			LL tp = mod_mul(f[i], h[i - j], pw[sz - j]);
			if(!tp)
				continue;
			g[j] = mod_add(g[j], mod_mul(tp, c[i][j], pw[sz - j]), pw[sz - j]);
		}
	}
}
pair<LL, LL> mod_fact(LL n) { // n = (v mod pp) * p^e -> (v, e)
	// parse
	static int len, dig[maxl];
	len = 0;
	for(LL tmp = n; tmp > 0; dig[len++] = tmp % p, tmp /= p);
	// init
	pair<LL, LL> ret = make_pair(1, 0);
	LL val = 0;
	memset(f, 0, sz * sizeof(LL));
	f[0] = 1;
	// iterate
	for(int i = len - 1; i >= 0; --i) {
		// update [1 .. tp), [tp .. tp + r]
		ret.first = mod_mul(ret.first, f[0], pp);
		ret.second += val;
		val *= p;
		LL last = val;
		for(int j = 1; j <= dig[i]; ++j)
			ret.first = mod_mul(ret.first, ++val, pp);
		//printf("%I64d : %I64d * %d ^ %I64d mod %I64d\n", val, ret.first, p, ret.second, pp);
		if(i == 0)
			continue;
		// f : [1 .. sp) -> [1 .. spp)
		if(last) {
			if(p == 2) {
				poly_val(f, last, g[0], g[1]); // 0 -> 1
				poly_mul(f, g[0], g[1]); // 0 -> 01
			} else { // p == 5
				poly_val(f, last, g[0], g[2]); // 0 -> 1
				poly_mul(g[0], f, g[2]); // 1 -> 01
				poly_val(g[0], last << 1, g[1], g[2]); // 01 -> 23
				poly_mul(g[1], g[0], g[2]); // 23 -> 0123
				poly_val(g[1], last, g[0], g[2]); // 0123 -> 1234
				poly_mul(f, g[0], g[2]); // 0 -> 01234
			}
		}
		// f : [1 .. spp) -> [1 .. tp)
		if(dig[i]) {
			poly_val(s[dig[i]], last * p, g[0], g[1]);
			poly_mul(f, g[0], g[1]);
		}
	}
	return ret;
}
void init(int _p, int _sz) {
	p = _p;
	sz = _sz;
	pw[0] = pp = 1;
	for(int i = 1; i <= sz; ++i)
		pw[i] = (pp *= p);
	// s[0] = 1
	memset(s[0], 0, sz * sizeof(LL));
	s[0][0] = 1;
	// s[1] = (x + 1) * (x + 2) * ... * (x + p-1)
	memcpy(s[1], s[0], sz * sizeof(LL));
	for(int i = 1; i < p; ++i)
		for(int j = sz - 1; j >= 0; --j) {
			s[1][j] = mod_mul(s[1][j], i, pw[sz - j]);
			if(j == 0)
				continue;
			s[1][j] = mod_add(s[1][j - 1] % pw[sz - j], s[1][j], pw[sz - j]);
		}
	// s[i] = s[i - 1] * s[1]((i - 1) p)
	for(int i = 2, j = p; i < p; ++i, j += p) {
		poly_val(s[1], j, s[i], g[0]);
		poly_mul(s[i], s[i - 1], g[0]);
	}
	// c[i][j] = binom(i, j) mod p^(sz - j)
	for(int i = 0; i < sz; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = mod_add(c[i - 1][j - 1] % pw[sz - j], c[i - 1][j], pw[sz - j]);
	}
}
void check(pair<LL, LL> all) {
	LL val = 0;
	if(all.second < sz)
		for(val = all.first; all.second--; val = mod_mul(val, p, pp));
	else
		val = 0;
	CRT(val);
}
int main()
{
	LL n;
	scanf("%lld", &n);
	ans = 0, mod = 1;
	init(2, 18);
	pair<LL, LL> all = mod_fact(n);
	int lastp = p;
	LL lastpp = pp;
	pair<LL, LL> lastall = all;
	init(5, 18);
	all = mod_fact(n);
	LL exp = min(lastall.second, all.second);
	all.first = mod_mul(all.first, mod_inv(mod_pow(lastp, exp, pp), pp), pp);
	all.second -= exp;
	check(all);
	swap(p, lastp);
	swap(pp, lastpp);
	swap(all, lastall);
	all.first = mod_mul(all.first, mod_inv(mod_pow(lastp, exp, pp), pp), pp);
	all.second -= exp;
	check(all);
	printf("%lld\n", ans);
	return 0;
}
