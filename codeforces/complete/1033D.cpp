#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxp = 1e6 + 1, maxv = 25, maxc = (int)2e3 + 1;
int ptot, pr[maxp], d[maxp], cnt;
LL n, p[maxc];
LL mod_add(LL x, LL y, LL p) {
	return (x += y) < p ? x : x - p;
}
LL mod_mul(LL x, LL y, LL p) {
	LL ret = x * y - (LL)((long double)x * y / p + 0.5) * p;
	return ret < 0 ? ret + p : ret;
}
LL mod_pow(LL x, LL k, LL p) {
	LL ret = 1 % p;
	for( ; k > 0; k >>= 1, x = mod_mul(x, x, p))
		(k & 1) && (ret = mod_mul(ret, x, p));
	return ret;
}
bool miller_rabin(LL n) {
	if(n == 2) return 1;
	if(n < 2 || !(n & 1))
		return 0;
	LL s = 0, r = n - 1;
	for( ; !(r & 1); r >>= 1, ++s);
	for(int i = 0; pr[i] < n && pr[i] < maxv; ++i) {
		LL cur = mod_pow(pr[i], r, n), nxt;
		for(int j = 0; j < s; ++j) {
			nxt = mod_mul(cur, cur, n);
			if(nxt == 1 && cur != 1 && cur != n - 1) return 0;
			cur = nxt;
		}
		if(cur != 1) return 0;
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
	static LL seq[maxp];
	while(1) {
		LL x = rand() % n, y = x, c = rand() % n;
		LL *px = seq, *py = seq, tim = 0, prd = 1;
		while(1) {
			*py++ = y = mod_add(mod_mul(y, y, n), c, n);
			*py++ = y = mod_add(mod_mul(y, y, n), c, n);
			if((x = *px++) == y) break;
			LL tmp = prd;
			prd = mod_mul(prd, abs(y - x), n);
			if(!prd) return gcd(tmp, n);
			if((++tim) == maxv) {
				if((prd = gcd(prd, n)) > 1 && prd < n) return prd;
				tim = 0;
			}
		}
		if(tim && (prd = gcd(prd, n)) > 1 && prd < n) return prd;
	}
}
void decompose(LL n) {
	for(int i = 0; i < cnt; ++i)
		if(n % p[i] == 0) {
			p[cnt++] = p[i];
			n /= p[i];
		}
	if(n < maxp) {
		for( ; n > 1; p[cnt++] = d[n], n /= d[n]);
	} else if(miller_rabin(n)) {
		p[cnt++] = n;
	} else {
		LL fact = pollard_rho(n);
		decompose(fact), decompose(n / fact);
	}
} // prepare pr(prime) and d(minimal factor)
int main() {
	for(int i = 2; i < maxp; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	int m, mod = 998244353;
	scanf("%d", &m);
	while(m--) {
		scanf("%lld", &n);
		decompose(n);
	}
	sort(p, p + cnt);
	int ans = 1;
	for(int i = 0; i < cnt; ) {
		int ctr = 0;
		for(LL pp = p[i]; i < cnt && p[i] == pp; ++i, ++ctr);
		ans = ans * (ctr + 1LL) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
