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

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, q;
    scanf("%d%d", &n, &q);
	set<pair<int, int> > seg;
	vector<i64> bits(n + 1), col(n + 1);
	seg.insert({1, 1});
	seg.insert({n + 1, 0});
	while(q--) {
		static char op[7];
		int x, y, z;
		scanf("%s%d%d", op, &x, &y);
		if(op[0] == 'C') {
			scanf("%d", &z);
		}
		switch(op[0]) {
			case 'C': {
				++y;
				auto it = seg.lower_bound({x + 1, 0});
				auto jt = it--;
				// printf("[%d, %d): %lld\n", x, min(jt -> first, y), col[it -> second]);
				for(int i = x; i <= n; i += i & -i)
					bits[i] += col[it -> second];
				for(int i = min(jt -> first, y); i <= n; i += i & -i)
					bits[i] -= col[it -> second];
				if(jt -> first > y) {
					// printf("add %d: %d\n", y, it -> second);
					seg.insert({y, it -> second});
				}
				if(it -> first == x) {
					// printf("del %d: %d\n", x, it -> second);
					seg.erase({x, it -> second});
				}
				// printf("add %d: %d\n", x, z);
				seg.insert({x, z});
				for(it = jt++; it -> first < y; it = jt++) {
					if(jt -> first >= y) {
						// printf("[%d, %d): %lld\n", it -> first, y, col[it -> second]);
						for(int i = it -> first; i <= n; i += i & -i)
							bits[i] += col[it -> second];
						for(int i = y; i <= n; i += i & -i)
							bits[i] -= col[it -> second];
						if(jt -> first > y) {
							// printf("add %d: %d\n", y, it -> second);
							seg.insert({y, it -> second});
						}
						// printf("del %d: %d\n", it -> first, it -> second);
						seg.erase(it);
						break;
					}
					// printf("[%d, %d): %lld\n", it -> first, jt -> first, col[it -> second]);
					for(int i = it -> first; i <= n; i += i & -i)
						bits[i] += col[it -> second];
					for(int i = jt -> first; i <= n; i += i & -i)
						bits[i] -= col[it -> second];
					// printf("del %d: %d\n", it -> first, it -> second);
					seg.erase(it);
				}
				// printf("[%d, %d): %lld\n", x, y, -col[z]);
				for(int i = x; i <= n; i += i & -i)
					bits[i] -= col[z];
				for(int i = y; i <= n; i += i & -i)
					bits[i] += col[z];
				break;
			}
			case 'A': {
				col[x] += y;
				break;
			}
			case 'Q': {
				i64 ans = col[(--seg.lower_bound({x + 1, 0})) -> second];
				for(int i = x; i > 0; i -= i & -i)
					ans += bits[i];
				printf("%lld\n", ans);
			}
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