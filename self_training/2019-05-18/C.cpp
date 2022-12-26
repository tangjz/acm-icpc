#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 11;
int t, n;
struct Point {
	LL x, y;
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	bool operator < (Point const &t) const {
		return det(t) < 0;
	}
} p[maxn], low, upp;
LL solve(Point L, Point R) {
	LL dt = L.x / L.y;
	L.x -= dt * L.y;
	R.x -= dt * R.y;
	if(!L.x || R.x > R.y)
		return R.y / R.x + 1;
	return solve((Point){R.y, R.x}, (Point){L.y, L.x}) * R.y / R.x + 1;
}
void solve() {
	low = (Point){0, 1};
	upp = (Point){1, 0};
	scanf("%d", &n);
	bool chk = 1;
	for(int i = 0; i < n; ++i) {
		scanf("%lld%lld", &p[i].x, &p[i].y);
		if(!chk)
			continue;
		for(int j = 0; j < i; ++j) {
			if(!chk)
				continue;
			LL dx = p[i].x - p[j].x;
			LL dy = p[i].y - p[j].y;
			LL com = __gcd(abs(dx), abs(dy));
			if(dy < 0) {
				if(dx <= 0) {
					chk = 0;
					continue;
				}
				upp = min(upp, (Point){dx / com, -dy / com});
			} else if(!dy) {
				if(dx <= 0) {
					chk = 0;
					continue;
				}
			} else {
				if(dx < 0)
					low = max(low, (Point){-dx / com, dy / com});
			}
		}
	}
	if(!chk || !(low < upp)) {
		puts("IMPOSSIBLE");
		return;
	}
	assert(low.y > 0);
	// for(LL x = 1; ; ++x) {
	// 	LL L = x * low.x / low.y + 1;
	// 	LL R = upp.y ? (x * upp.x - 1) / upp.y : L;
	// 	if(L <= R) {
	// 		printf("%lld %lld\n", x, L);
	// 		return;
	// 	}
	// }
	if(!upp.y) {
		printf("%lld %lld\n", 1LL, low.x / low.y + 1);
		return;
	}
	LL x = max(solve(low, upp), 1LL);
	LL y = max(x * low.x / low.y + 1, 1LL);
	printf("%lld %lld\n", x, y);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}