#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn = (LL)1e12 + 1;
const int maxm = (int)1e6 + 1;
int tot, pr[maxm], d[maxm];
LL ipow(LL x, int k) {
	LL ret = 1;
	for( ; k > 0; x *= x, k >>= 1)
		(k & 1) && (ret *= x);
	return ret;
}
LL solve(LL lim) {
	set<LL> Hash;
	for(int e = 2; e < 40; ++e)
		for(int p = 2; ipow(p, e) <= lim; ++p)
			if(d[e] < e || d[p] < p)
				Hash.insert(ipow(p, e));
	if(Hash.count(16))
		Hash.erase(16);
	LL ret = 0;
	for(auto val: Hash)
		ret += val;
	return ret;
}
int main() {
	for(int i = 2; i < maxm; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	printf("%lld\n", solve((LL)1e12));
	return 0;
}
