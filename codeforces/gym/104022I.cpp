#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int maxd = 32001;
const LL maxv = (LL)1e18 + 1;
int d[maxd], ptot, pr[maxd];
vector<LL> fib;
void init() {
	for(int i = 2; i < maxd; ++i) {
		if(!d[i])
			pr[ptot++] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxd; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	fib = {0LL, 1LL};
	while(fib.back() < maxv)
		fib.push_back(fib.back() + *(++fib.rbegin()));
}
vector<PII> factorize(int m) {
	vector<PII> ret;
	for(int i = 0; pr[i] * pr[i] <= m; ++i) {
		if(m % pr[i] > 0)
			continue;
		PII fct = {pr[i], 1};
		do {
			m /= pr[i];
			fct.second *= pr[i];
		} while(m % pr[i] == 0);
		ret.push_back(fct);
	}
	if(m > 1)
		ret.push_back({m, m});
	return ret;
}
inline int mod_pow(int x, int k, int m) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % m)
		if(k & 1)
			ret = (LL)ret * x % m;
	return ret;
}
inline int mod_pow_sum(int x, int k, int m) {
	int ret = 0, sum = 1;
	for( ; k > 0; k >>= 1, sum = sum * (x + 1LL) % m, x = (LL)x * x % m)
		if(k & 1)
			ret = ((LL)ret * x + sum) % m;
	return ret;
}
bool is_small_fib(int x, int k, int m) {
	if(x == k)
		return 1 < m;
	return x < (int)fib.size() && fib[x] / fib[k] < m;
}
PII get_fib(int k, int m) {
	if(m == 1)
		return {0, 0};
	if(k < (int)fib.size())
		return {(int)(k ? fib[k - 1] % m : 1), (int)(fib[k] % m)};
	// I = {1, 0}, A = {0, 1}, A^k = {fib(k - 1), fib(k)}
	auto merge = [&](PII lft, PII rht) -> PII {
		int fir = ((LL)lft.first * rht.first + (LL)lft.second * rht.second) % m;
		int sec = ((LL)lft.second * rht.first + ((LL)lft.first + lft.second) * rht.second) % m;
		return {fir, sec};
	};
	PII ret = {1, 0}, x = {0, 1};
	for( ; k > 0; k >>= 1, x = merge(x, x))
		if(k & 1)
			ret = merge(ret, x);
	return ret;
}
int get_fib_div(PII tr, int k, int m) {
	if(m == 1)
		return 0;
	// I = {{1, 0}, {0, 0}}, A = {{tr.first, 0}, {0, tr.second / tr.second}}, A^k = {{?, ?}, {0, ret}}
	typedef pair<PII, int> PIII;
	auto merge = [&](PIII lft, PIII rht) -> PIII {
		int &aL = lft.first.first, &bL = lft.first.second, &cL = lft.second;
		int &aR = rht.first.first, &bR = rht.first.second, &cR = rht.second;
		int u = (aL + (LL)bL * tr.second) % m;
		int v = (LL)cL * tr.second % m;
		int a = (LL)aL * aR % m;
		int b = ((LL)bL * aR + (LL)u * bR + (LL)v * cR) % m;
		int c = ((LL)cL * aR + (LL)v * bR + ((LL)u + v) * cR) % m;
		return {{a, b}, c};
	};
	PIII ret = {{1, 0}, 0}, x = {{tr.first, 0}, 1};
	for( ; k > 0; k >>= 1, x = merge(x, x))
		if(k & 1)
			ret = merge(ret, x);
	return ret.second;
}
int solve() {
	int x, y, a, m;
	scanf("%d%d%d%d", &x, &y, &a, &m);
	if(!(a %= m))
		return 1 % m;
	// assert(m > 1);
	int z = __gcd(x, y), per = m;
	vector<PII > fcts = factorize(m);
	for(auto &it: fcts)
		per -= per / it.first;
	int prd = get_fib(z, per).second;
	prd = mod_pow(a, prd + (is_small_fib(z, 1, per) ? 0 : per), m);
	if(!prd)
		return 1;
	per = m;
	for(auto &it: fcts)
		if(prd % it.first != 1)
			per -= per / it.first;
	PII base = get_fib(z, per);
	int lft = get_fib_div(base, x / z, per);
	int rht = get_fib_div(base, y / z, per);
	lft = mod_pow_sum(prd, lft + (is_small_fib(x, z, per) ? 0 : per), m);
	rht = mod_pow_sum(prd, rht + (is_small_fib(y, z, per) ? 0 : per), m);
	return (LL)lft * rht % m;
}
int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("%d\n", solve());
	}
	return 0;
}