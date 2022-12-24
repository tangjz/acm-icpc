#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL exgcd(LL a, LL b, LL &x, LL &y) {
	if(!b) return x = 1, y = 0, a;
	LL r = exgcd(b, a % b, y, x);
	return y -= a / b * x, r;
}
inline pair<LL, LL> CRT(LL a1, LL m1, LL a2, LL m2) {
	LL x, y, r = exgcd(m1, m2, x, y);
	if((a2 - a1) % r > 0) return make_pair(0LL, 0LL);
	x = (a2 - a1) % m2 * x % m2 / r;
	return make_pair(m1 * (x < 0 ? x + m2 / r : x) + a1, m1 / r * m2);
}
int mod, gen, ord;
LL L, R, ans;
int main() {
	scanf("%d%lld%lld%d", &mod, &L, &R, &ord);
	if(!ord) {
		printf("%lld\n", R / mod - (L - 1) / mod);
		return 0;
	}
	for(gen = 1; gen < mod; ++gen) {
		int i = 1, v = gen;
		for( ; i < mod - 1 && v != 1; ++i, v = (LL)v * gen % mod);
		if(i == mod - 1)
			break;
	}
	for(int i = 0, v = 1; i < mod - 1; ++i, v = (LL)v * gen % mod)
		if(ord == v) {
			ord = i;
			break;
		}
	for(int i = 0, v = 1; i < mod - 1; ++i, v = (LL)v * gen % mod) {
		LL x, y, r = exgcd(i, mod - 1, x, y);
		if(ord % r > 0)
			continue;
		pair<LL, LL> res = CRT(v, mod, ord * (x < 0 ? x + mod - 1 : x) % (mod - 1) / r, (mod - 1) / r);
		assert(res.second != 0);
		ans += (res.first <= R ? (R - res.first) / res.second : -1) - (res.first < L ? (L - 1 - res.first) / res.second : -1);
	}
	printf("%lld\n", ans);
	return 0;
}