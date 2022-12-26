#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL mod_add(LL x, LL y, LL mod) {
	return (x += y) < mod ? x : x - mod;
}
inline LL mod_mul(LL x, LL y, LL mod) {
	typedef long double LD;
	LL ret = x * y - (LL)((LD)x * y / mod + 0.5) * mod;
	return ret < 0 ? ret + mod : ret;
}
inline LL mod_pow(LL x, LL k, LL mod) {
	LL ret = mod > 1 ? 1 : 0;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, mod))
		if(k & 1)
			ret = mod_mul(ret, x, mod);
	return ret;
}
inline LL int_pow(LL x, int k, LL upp) {
	LL ret = 1, lim = (++upp) / x;
	for( ; k > 0; --k) {
		if(ret > lim)
			return upp;
		ret *= x;
	}
	return ret;
}
inline bool miller_rabin(LL n) {
	if(n == 2)
		return 1;
	if(n < 2 || !(n & 1))
		return 0;
	LL s, r;
	for(s = 0, r = n - 1; !(r & 1); r >>= 1, ++s);
	static const int ptot = 12, pr[ptot] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int p : pr) {
		if(p >= n)
			break;
		LL cur = 1, nxt = p;
		for(LL k = r; k > 0; k >>= 1, nxt = mod_mul(nxt, nxt, n))
			if(k & 1)
				cur = mod_mul(cur, nxt, n);
		for(int i = 0; i < s; ++i) {
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
inline LL pollard_rho(LL n) {
	static mt19937_64 rnd(996);
	while(1) {
		LL x = rnd() % (n - 3) + 2, y = x, c = rnd() % n, tim = 0, prd = 1;
		for(LL i = 1, stp = 2; ; ++i) {
			if(i == stp) {
				y = x;
				stp <<= 1;
			}
			if((x = mod_add(mod_mul(x, x, n), c, n)) == y)
				break;
			LL tmp = prd;
			if((prd = mod_mul(prd, abs(y - x), n)) == 0)
				return __gcd(tmp, n);
			static const int maxt = 100;
			if((++tim) < maxt)
				continue;
			if((prd = __gcd(prd, n)) > 1)
				return prd;
			tim = 0;
		}
		if(tim > 0 && (prd = __gcd(prd, n)) > 1)
			return prd;
	}
	assert(0);
}
inline void getPrimeFactors(LL n, int &tot, LL pr[]) {
	tot = 0;
	queue<LL> que;
	que.push(n);
	while(!que.empty()) {
		LL x = que.front();
		que.pop();
		for(int i = 0; i < tot; ++i)
			for(LL y = pr[i]; x % y == 0; x /= y);
		if(x == 1)
			continue;
		if(miller_rabin(x)) {
			pr[tot++] = x;
		} else {
			LL y = pollard_rho(x);
			que.push(y);
			que.push(x / y);
		}
	}
	sort(pr, pr + tot);
}
const int maxn = (int)1e5 + 1, maxp = 15, maxe = 51, mod = 998244353;
int t, tot, a[maxp], b[maxp], fct[maxe], ifct[maxe];
LL n, pr[maxe];
int main() {
	ifct[1] = 1;
	for(int i = 2; i < maxe; ++i)
		ifct[i] = mod - (int)(mod / i * (LL)ifct[mod % i] % mod);
	fct[0] = ifct[0] = 1;
	for(int i = 1; i < maxe; ++i) {
		fct[i] = (LL)fct[i - 1] * i % mod;
		ifct[i] = (LL)ifct[i - 1] * ifct[i] % mod;
	}
	scanf("%lld%d", &n, &t);
	getPrimeFactors(n, tot, pr);
	while(t--) {
		LL u, v;
		scanf("%lld%lld", &u, &v);
		int c0 = 0, c1 = 0, ans = 1;
		for(int i = 0; i < tot; ++i) {
			LL p = pr[i];
			for(a[i] = 0; u % p == 0; u /= p, ++a[i]);
			for(b[i] = 0; v % p == 0; v /= p, ++b[i]);
			int com = min(a[i], b[i]);
			c0 += (a[i] -= com);
			c1 += (b[i] -= com);
			ans = (LL)ans * ifct[a[i]] % mod * ifct[b[i]] % mod;
		}
		ans = (LL)ans * fct[c0] % mod * fct[c1] % mod;
		printf("%d\n", ans);
	}
	return 0;
}