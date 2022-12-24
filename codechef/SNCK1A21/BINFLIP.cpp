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
    int n, k;
	scanf("%d%d", &n, &k);
	if(!k) {
		puts("YES\n0");
		return;
	}
	if(!(k & 1)) {
		puts("NO");
		return;
	}
	int mx = 0;
	for( ; (1 << mx) <= k; ++mx);
	int sta = 1, upp = n, rem = k;
	vector<int> ans;
	for(int i = mx - 1; i >= 0; --i) {
		if((1 << i) <= rem) {
			rem -= 1 << i;
			ans.push_back(sta + rem);
		} else {
			ans.push_back(sta);
			sta += rem;
			rem = (1 << i) - rem;
		}
		upp = min(upp, 1 << i);
		assert(sta + upp - 1 <= n);
	}
	puts("YES");
	printf("%d\n", mx);
	for(int i = 0; i < mx; ++i) {
		printf("%d\n", ans.back());
		ans.pop_back();
	}
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}