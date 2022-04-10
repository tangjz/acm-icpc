#include <bits/stdc++.h>
using namespace std;
 
typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;
 
const int maxn = (int)1e5 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;
 
inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}
 
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
};
 
void solve() {
	int n;
	static Point p[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		p[i].read();
	int ans = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j) {
			bool fir = 1;
			int pL, pR;
			for(int k = 0; k < n; ++k) {
				if(k == i || k == j)
					continue;
				int tmp = p[i].det(p[j]) + p[j].det(p[k]) + p[k].det(p[i]);
				if(fir) {
					pL = pR = tmp;
					fir = 0;
				} else {
					ans = max(ans, abs(tmp - pL));
					ans = max(ans, abs(tmp - pR));
					pL = min(pL, tmp);
					pR = max(pR, tmp);
				}
			}
		}
	printf("%d.%c\n", ans / 2, "05"[ans & 1]);
}
 
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}