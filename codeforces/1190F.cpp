#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
inline LL mod_add(LL x, LL y, LL mod) {
	return (x += y) < mod ? x : x - mod;
}
inline LL mod_mul(LL x, LL y, LL mod) {
	const int BLEN = __builtin_clzll(mod) - 1;
	const LL BMSK = (1LL << BLEN) - 1;
	LL ret = 0;
	if(x < y)
		swap(x, y);
	while(y > 0) {
		ret += x * (y & BMSK);
		ret = ret < mod ? ret : ret % mod;
		y >>= BLEN;
		x <<= BLEN;
		x = x < mod ? x : x % mod;
	}
	return ret;
/*
	typedef long double LD;
	LL ret = x * y - (LL)((LD)x * y / mod + 0.5) * mod;
	return ret < 0 ? ret + mod : ret;
*/
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
inline vector<pair<LL, LL> > factorize(LL n) {
	vector<LL> vec;
	queue<LL> que;
	que.push(n);
	while(!que.empty()) {
		LL x = que.front();
		que.pop();
		for(LL y : vec)
			for( ; x % y == 0; x /= y, vec.push_back(y));
		if(x == 1)
			continue;
		if(miller_rabin(x)) {
			vec.push_back(x);
		} else {
			LL y = pollard_rho(x);
			que.push(y);
			que.push(x / y);
		}
	}
	sort(vec.begin(), vec.end());
	vector<pair<LL, LL> > ret;
	for(LL x : vec)
		if(!ret.empty() && ret.back().first == x) {
			++ret.back().second;
		} else {
			ret.push_back(make_pair(x, 1LL));
		}
	return ret;
}
 
const int maxn = (int)5e5 + 1, maxe = 60;
int n;
LL m, sp, pr, ex, phi, ord, gen;
void init() {
	scanf("%d%lld%lld", &n, &m, &sp);
	for(ex = maxe - 1; ex >= 1; --ex) {
		if(m < (1LL << ex))
			continue;
		LL low = 2, upp;
		for(upp = low << 1; int_pow(upp, ex, m) <= m; upp <<= 1);
		while(low < upp) {
			LL mid = (low + upp + 1) >> 1;
			if(int_pow(mid, ex, m) <= m) {
				low = mid;
			} else {
				upp = mid - 1;
			}
		}
		if(int_pow(low, ex, m) == m) {
			pr = low;
			break;
		}
	}
	assert(ex >= 1 && miller_rabin(pr));
	phi = m - m / pr;
	if(sp % pr == 0) {
		ord = gen = -1;
		return;
	}
	ord = phi;
	vector<pair<LL, LL> > vec = factorize(pr - 1);
	if(ex > 1)
		vec.push_back(make_pair(pr, ex - 1));
	for(pair<LL, LL> it : vec)
		for( ; it.second > 0 && mod_pow(sp, ord / it.first, m) == 1; --it.second, ord /= it.first);
	if(pr == 2 && m >= 8) {
		assert((sp & 3) != 3 || !(ord & 1));
		LL half_phi = phi / 2;
		for(gen = 1; gen < m; gen += 4) {
			bool chk = mod_pow(gen, half_phi, m) == 1;
			for(pair<LL, LL> it : vec)
				chk &= mod_pow(gen, half_phi / it.first, m) != 1;
			if(chk)
				break;
		}
	} else {
		for(gen = 0; gen < m; ++gen) {
			bool chk = mod_pow(gen, phi, m) == 1;
			for(pair<LL, LL> it : vec)
				chk &= mod_pow(gen, phi / it.first, m) != 1;
			if(chk)
				break;
		}
	}
}
void solve() {
	if(n > phi - abs(ord)) {
		puts("-1");
		return;
	}
	if(ord == -1) {
		LL val = 1;
		for(int i = 1; i <= n; ++i) {
			for(++val; val < m && val % pr == 0; ++val);
			assert(val < m);
			printf("%lld%c", val, " \n"[i == n]);
		}
		return;
	}
	if(pr == 2 && m >= 8 && (sp & 3) == 3) {
		LL upp = phi / 2, stp = upp / (ord / 2);
		for(LL e = 0, u = 1, v = sp; e < upp && n > 0; ++e, u = mod_mul(u, gen, m), v = mod_mul(v, gen, m))
			if(e % stp > 0) {
				printf("%lld%c", u, " \n"[!(--n)]);
				if(n > 0)
					printf("%lld%c", v, " \n"[!(--n)]);
			}
	} else {
		LL upp = pr == 2 ? phi / 2 : phi, stp = upp / ord;
		for(LL e = 0, v = 1; e < upp && n > 0; ++e, v = mod_mul(v, gen, m)) {
			if(e % stp > 0)
				printf("%lld%c", v, " \n"[!(--n)]);
			if(n > 0 && pr == 2)
				printf("%lld%c", m - v, " \n"[!(--n)]);
		}
	}
	assert(n == 0);
}
int main() {
	init();
	solve();
	return 0;
}