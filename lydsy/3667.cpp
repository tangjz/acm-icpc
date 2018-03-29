#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LDB;
const int maxv = 1 << 16 | 1, maxp = 24, maxt = 20;
int ptot, pr[maxv], d[maxv];
inline LL mod_add(LL x, LL y, LL mod) {
	return (x += y) < mod ? x : x - mod;
}
inline LL mod_mul(LL x, LL y, LL mod) {
	return (x = x * y - (LL)((LDB)x * y / mod + 0.5) * mod) < 0 ? x + mod : x;
}
inline LL mod_pow(LL x, LL y, LL mod) {
	LL ret = 1;
	for( ; y > 0; y >>= 1, x = mod_mul(x, x, mod))
		(y & 1) && (ret = mod_mul(ret, x, mod));
	return ret;
}
bool miller_rabin(LL n) {
	if(n == 2)
		return 1;
	if(n < 2 || !(n & 1))
		return 0;
	int s = 0;
	LL r = n - 1;
	for( ; !(r & 1); r >>= 1, ++s);
	for(int i = 0; pr[i] < maxp && pr[i] < n; ++i) {
		LL cur = mod_pow(pr[i], r, n), nxt;
		for(int j = 0; j < s; ++j) {
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
LL gcd(LL a, LL b) {
	int ret = 0;
	while(a) {
		for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
		for( ; !(a & 1); a >>= 1);
		for( ; !(b & 1); b >>= 1);
		if(a < b)
			swap(a, b);
		a -= b;
	}
	return b << ret;
}
LL pollard_rho(LL n) {
	static LL seq[(maxv + maxt) | 1];
	while(1) {
		int tim = 0;
		LL x = rand() % n, y = x, c = rand() % n;
		LL *px = seq, *py = seq, prd = 1, las;
		while(1) {
			*py++ = y = mod_add(mod_mul(y, y, n), c, n);
			*py++ = y = mod_add(mod_mul(y, y, n), c, n);
			x = *px++;
			if(x == y)
				break;
			las = prd;
			prd = mod_mul(prd, std::abs(y - x), n);
			if(!prd)
				return gcd(las, n);
			if((++tim) == maxt) {
				prd = gcd(prd, n);
				if(prd > 1 && prd < n)
					return prd;
				tim = 0;
			}
		}
		if(tim) {
			prd = gcd(prd, n);
			if(prd > 1 && prd < n)
				return prd;
		}
	}
}
LL factorize(LL n) {
	LL ret = 1;
	queue<LL> que;
	que.push(n);
	while(!que.empty()) {
		LL val = que.front();
		que.pop();
		if(val < maxv) {
			for( ; val > 1; val /= d[val])
				ret = max(ret, (LL)d[val]);
		} else if(miller_rabin(val)) {
			ret = max(ret, val);
		} else {
			LL part = pollard_rho(val);
			que.push(part);
			que.push(val / part);
		}
	}
	return ret;
}
int main() {
	for(int i = 2; i < maxv; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int t;
	LL n;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		LL m = factorize(n);
		if(m == 1 || m < n)
			printf("%lld\n", m);
		else
			puts("Prime");
	}
	return 0;
}
