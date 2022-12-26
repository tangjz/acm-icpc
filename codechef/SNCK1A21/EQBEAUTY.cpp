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
	int n;
	static int a[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	if(n == 2) {
		puts("0");
		return;
	}
	if(n == 3) {
		printf("%d\n", min(a[2] - a[1], a[1] - a[0]));
		return;
	}
	int pL = (n - 1) / 2, pR = (n + 1) / 2;
	i64 lft = 0, rht = 0;
	for(int i = 1; i < n; ++i) {
		lft += abs(a[i - 1] - a[pL]);
		rht += abs(a[i] - a[pR]);
	}
	int ans = min(min(lft, rht), (i64)INT_MAX);
	for(int i = 1, j = n - 2; i + 1 < n; ++i) {
		for(j = max(j, i + 1); i < j && a[i] - a[0] > a[n - 1] - a[j]; --j);
		if(i < j) {
			ans = min(ans, abs((a[i] - a[0]) - (a[n - 1] - a[j])));
		}
		if(j + 1 < n - 1) {
			ans = min(ans, abs((a[i] - a[0]) - (a[n - 1] - a[j + 1])));
		}
	}
	printf("%d\n", ans);
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
