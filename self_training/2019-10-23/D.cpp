#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef LL Matrix[2][2];
inline LL &modFixed(LL &x, LL p) {
	x = x >= 0 && x < p ? x : x % p;
	return x < 0 ? (x += p) : x;
}
inline LL modMulti(LL x, LL y, LL p, LL adt = 0) {
	LL ret = modFixed(adt, p);
	if(!modFixed(x, p) || !modFixed(y, p))
		return ret;
	/*
	const int BLEN = __builtin_clzll(p) - 1;
	const LL BMSK = (1LL << BLEN) - 1;
	if(x < y)
		swap(x, y);
	while(y > 0) {
		modFixed(ret += x * (y & BMSK), p);
		y >>= BLEN;
		modFixed(x <<= BLEN, p);
	}
	//
	ret = (ret + (__int128_t)x * y) % p;
	*/
	modFixed(ret += x * y - (LL)((long double)x * y / p + 0.5) * p, p);
	return ret;
}
inline void matMulti(Matrix &ret, Matrix const &lft, Matrix const &rht, LL p) {
	Matrix tmp = {};
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
				tmp[i][k] = modMulti(lft[i][j], rht[j][k], p, tmp[i][k]);
	memcpy(ret, tmp, sizeof(Matrix));
}
int main() {
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		LL n, a, b, p;
		scanf("%lld%lld%lld%lld", &n, &a, &b, &p);
		if(p == 1) {
			puts("0");
			continue;
		}
		Matrix ans = {}, tmp = {};
		ans[0][0] = ans[1][1] = tmp[0][1] = 1;
		tmp[1][0] = modFixed(a, p);
		tmp[0][0] = tmp[1][1] = modFixed(b, p);
		while(n > 0) {
			if(n & 1)
				matMulti(ans, ans, tmp, p);
			n >>= 1;
			matMulti(tmp, tmp, tmp, p);
		}
		printf("%lld\n", ans[0][0]);
	}
	return 0;
}
