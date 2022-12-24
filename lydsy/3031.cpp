#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
vector<pair<LL, int> > factorize(LL x) {
	static bool enabled = 0;
	static int tot, pr[maxn >> 3 | 1], d[maxn];
	if(!enabled) {
		tot = 0;
		memset(d, 0, sizeof d);
		for(int i = 2; i < maxn; ++i) {
			if(!d[i])
				pr[tot++] = d[i] = i;
			for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
				d[k] = pr[j];
				if(d[i] == pr[j])
					break;
			}
		}
		pr[tot] = maxn;
		enabled = 1;
	}
	vector<pair<LL, int> > ret;
	for(int i = 0; (LL)pr[i] * pr[i] <= x; ++i)
		if(x % pr[i] == 0) {
			int cnt = 0;
			do {
				x /= pr[i];
				++cnt;
			} while(x % pr[i] == 0);
			ret.push_back(make_pair((LL)pr[i], cnt));
		}
	if(x > 1)
		ret.push_back(make_pair(x, 1));
	return ret;
}
LL phi(LL x) {
	LL ret = x;
	vector<pair<LL, int> > fcts = factorize(x);
	for(vector<pair<LL, int> >::iterator it = fcts.begin(); it != fcts.end(); ++it)
		ret -= ret / (it -> first);
	return ret;
}
inline LL mod_mul(LL x, LL y, LL m) {
	const int BLEN = 20, BMSK = (1 << BLEN) - 1;
	return ((((x >> BLEN) * y % m) << BLEN) + (x & BMSK) * y) % m;
}
LL mod_pow(LL x, LL k, LL m) {
	LL ret = 1;
	for( ; k > 0; x = mod_mul(x, x, m), k >>= 1)
		if(k & 1)
			ret = mod_mul(ret, x, m);
	return ret;
}
int main() {
	int t, m;
	LL a, b, k, r;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld%lld", &a, &b, &k);
		b /= __gcd(a, b);
		for(m = 0; (r = __gcd(b, k)) > 1; b /= r, ++m);
		if(b > 1) {
			r = phi(b);
			vector<pair<LL, int> > fcts = factorize(r);
			for(vector<pair<LL, int> >::iterator it = fcts.begin(); it != fcts.end(); ++it)
				for( ; (it -> second) > 0 && mod_pow(k, r / (it -> first), b) == 1; r /= it -> first);
		} else {
			r = 0;
		}
		printf("%d %lld\n", m, r);
	}
	return 0;
}