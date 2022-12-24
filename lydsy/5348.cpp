#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL mod_fix(LL x, LL m) {
	return x < m ? x : x % m;
}
inline LL mod_add(LL x, LL y, LL m) {
	return (x += y) < m ? x : x - m;
}
inline LL mod_mul(LL x, LL y, LL m) {
	const int BLEN = __builtin_clzll(m) - 1;
	const LL BMSK = (1LL << BLEN) - 1;
	LL ret = 0;
	if(x < y)
		swap(x, y);
	for( ; y > 0; y >>= BLEN, x = mod_fix(x << BLEN, m))
		if(y & BMSK)
			ret = mod_fix(ret + x * (y & BMSK), m);
	return ret;
}
inline LL mod_pow(LL x, LL k, LL m) {
	LL ret = m > 1 ? 1 : 0;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, m))
		if(k & 1)
			ret = mod_mul(ret, x, m);
	return ret;
}
inline bool miller_rabin(LL n) {
	if(!(n & 1) || n <= 2)
		return n == 2;
	int ex = 0;
	LL rem = n - 1;
	for( ; !(rem & 1); ++ex, rem >>= 1);
	static const int ptot = 12, prs[ptot] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i = 0; i < ptot; ++i) {
		LL pr = prs[i];
		if(pr >= n)
			break;
		LL cur = mod_pow(pr, rem, n);
		for(int i = 0; i < ex; ++i) {
			LL nxt = mod_mul(cur, cur, n);
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
	const int BLEN = 64 - __builtin_clzll(n);
	while(1) {
		int tim = 0;
		LL x = rand() % (n - 3) + 2, y = x, c = rand() % n, prd = 1;
		for(LL cur = 1, nxt = cur << 1; ; ++cur) {
			if(cur == nxt) {
				y = x;
				nxt <<= 1;
			}
			if((x = mod_add(mod_mul(x, x, n), c, n)) == y)
				break;
			LL tmp = prd;
			if((prd = mod_mul(prd, abs(y - x), n)) == 0)
				return __gcd(tmp, n);
			if((++tim) < BLEN)
				continue;
			if((prd = __gcd(prd, n)) > 1)
				return prd;
			tim = 0;
		}
		if(tim > 0 && (prd = __gcd(prd, n)) > 1)
			return prd;
	}
}
int main() {
	LL n, k, ans = 1;
	scanf("%lld%lld", &n, &k);
	map<LL, int> prs;
	queue<LL> que;
	for(que.push(n); !que.empty(); que.pop()) {
		LL x = que.front();
		for(map<LL, int>::iterator it = prs.begin(); it != prs.end(); ++it)
			for(LL pr = it -> first; x % pr == 0; x /= pr, ++(it -> second));
		if(miller_rabin(x)) {
			prs.insert(make_pair(x, 1));
		} else if(x > 1) {
			LL tmp = pollard_rho(x);
			que.push(tmp);
			que.push(x / tmp);
		}
	}
	for(map<LL, int>::iterator it = prs.begin(); it != prs.end(); ++it) {
		LL pr = it -> first, ex = it -> second, phi = pr - 1;
		for(int i = 1; i < ex; ++i)
			phi *= pr;
		if(pr == 2 && ex >= 3)
			phi /= 2;
		for(LL com; (com = __gcd(phi, k)) > 1; phi /= com);
		if(pr == 2 && ex >= 3)
			phi = phi * 2 - !(k & 1);
		ans *= phi + 1;
	}
	printf("%lld\n", ans);
	return 0;
}