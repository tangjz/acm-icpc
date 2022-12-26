#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = 1 << 20 | 1;
const LL maxv = (LL)1e12;

void solve() {
	int n, x;
	static pair<LL, LL> seg[maxn];
	assert(
		scanf("%d%d", &x, &n) == 2
		&& 1 <= n && n <= 100000
		&& 1 <= x && x <= 1000000
	);
	for(int i = 0; i < n; ++i) {
		assert(
			scanf("%lld%lld", &seg[i].first, &seg[i].second)
			&& 1 <= seg[i].first && seg[i].first <= seg[i].second && seg[i].second <= maxv
		);
	}
	if(!(x & 1)) {
		for(int i = 0; i < n; ++i)
			puts("0");
		return;
	}
	int mx = 1;
	for( ; mx <= x; mx <<= 1);
	static int s[maxm];
	s[0] = 0;
	LL val = 0;
	for(int i = 1; i <= mx; ++i, val += x) {
		s[i] = s[i - 1] + (gcd(val ^ x, (LL)x) == 1);
	}
	auto calc = [&](LL R) { // [0, R)
		return R / mx * s[mx] + s[R % mx];
	};
	for(int i = 0; i < n; ++i) {
		LL ans = calc(seg[i].second + 1) - calc(seg[i].first);
		printf("%lld\n", ans);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
