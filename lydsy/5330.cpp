#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxv = (int)1e7 + 1, maxe = 15, maxn = 103681, maxp = 24, maxt = 61;
int ptot, p[maxv], d[maxv];
int t, mod, etot, ex[maxe], ftot, f[maxn][maxe + 2], g[maxn];
LL n, m, pr[maxe], fct[maxn];
inline LL mod_add(LL x, LL y, LL mod) {
	return (x += y) < mod ? x : x - mod;
}
inline LL mod_mul(LL x, LL y, LL mod) {
	return (x = x * y - (LL)((long double)x * y / mod + 0.1) * mod) < 0 ? x + mod : x;
}
LL mod_pow(LL x, LL y, LL mod) {
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
	for(int i = 0; p[i] < maxp && p[i] < n; ++i) {
		LL cur = mod_pow(p[i], r, n), nxt;
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
inline LL gcd(LL a, LL b) {
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
	static LL seq[maxv];
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
void factorize(LL n, int &etot, LL pr[], int ex[]) {
	queue<LL> que;
	vector<LL> ret;
	que.push(n);
	while(!que.empty()) {
		LL val = que.front();
		que.pop();
		if(val < maxv) {
			for( ; val > 1; val /= d[val])
				ret.push_back((LL)d[val]);
		} else if(miller_rabin(val)) {
			ret.push_back(val);
		} else {
			LL tmp = pollard_rho(val);
			que.push(tmp);
			que.push(val / tmp);
		}
	}
	sort(ret.begin(), ret.end());
	etot = 0;
	for(vector<LL>::iterator it = ret.begin(); it != ret.end(); ++it)
		if(!etot || pr[etot - 1] != *it) {
			pr[etot] = *it;
			ex[etot++] = 1;
		} else {
			++ex[etot - 1];
		}
}
inline int getPower(LL k) {
	int ret = 1, tmp = m;
	for( ; k > 0; k >>= 1, tmp = (LL)tmp * tmp % mod)
		if(k & 1)
			ret = (LL)ret * tmp % mod;
	return ret;
}
int dfs(int dep, LL val, LL rem) {
	if(dep == etot) {
		int coeff = (val >> !(val & 1)) * rem % mod; // |val * rem| <= n
		coeff < 0 && (coeff += mod);
		return (LL)coeff * getPower((val + 1) >> 1) % mod;
	}
	LL ret = 0, tmp = rem * (1 - pr[dep]);
	if(pr[dep] & 1) // VAL can not be odd when REM is even
		ret += dfs(dep + 1, val, tmp);
	for(int i = 1; i < ex[dep]; ++i)
		ret += dfs(dep + 1, val *= pr[dep], tmp);
	ret += dfs(dep + 1, val *= pr[dep], rem);
	return ret % mod;
}
int main() {
	for(int i = 2; i < maxv; ++i) {
		if(!d[i])
			p[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * p[j]) < maxv; ++j) {
			d[k] = p[j];
			if(d[i] == p[j])
				break;
		}
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld%d", &n, &m, &mod);
		m %= mod;
		factorize(n, etot, pr, ex);
		printf("%d\n", dfs(0, 1, 1));
	}
	return 0;
}
