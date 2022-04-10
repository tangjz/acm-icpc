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
 
const int maxn = (int)1e3 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;
 
inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}
 
void solve() {
	int n, q;
	static i64 bits[4][maxn][maxn] = {};
	scanf("%d%d", &n, &q);
	auto upd = [&](int x, int y, i64 d) {
		if(x > n || y > n)
			return;
		i64 dx = x & 1 ? d : 0, dy = y & 1 ? d : 0, dxy = x & 1 ? dy : 0;
		for(int i = x; i <= n; i += i & -i)
			for(int j = y; j <= n; j += j & -j) {
				bits[0][i][j] ^= d;
				bits[1][i][j] ^= dx;
				bits[2][i][j] ^= dy;
				bits[3][i][j] ^= dxy;
			}
	};
	auto qry = [&](int x, int y) {
		if(x <= 0 || y <= 0)
			return 0LL;
		i64 r = 0, rx = 0, ry = 0, rxy = 0;
		for(int i = x; i > 0; i -= i & -i)
			for(int j = y; j > 0; j -= j & -j) {
				r ^= bits[0][i][j];
				rx ^= bits[1][i][j];
				ry ^= bits[2][i][j];
				rxy ^= bits[3][i][j];
			}
		if(!(x & 1)) {
			if(!(y & 1))
				rxy ^= r;
			rxy ^= ry;
		}
		if(!(y & 1)) {
			rxy ^= rx;
		}
		return rxy;
	};
	while(q--) {
		int t, xL, yL, xR, yR;
		i64 v;
		scanf("%d%d%d%d%d", &t, &xL, &yL, &xR, &yR);
		if(t == 1) {
			printf("%lld\n", qry(xR, yR) ^ qry(xL - 1, yR) ^ qry(xR, yL - 1) ^ qry(xL - 1, yL - 1));
		} else {
			scanf("%lld", &v);
			upd(xL, yL, v);
			upd(xL, yR + 1, v);
			upd(xR + 1, yL, v);
			upd(xR + 1, yR + 1, v);
		}
	}
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