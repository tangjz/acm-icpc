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

const int maxn = (int)2e3 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f, inv2 = (mod + 1) >> 1;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m, k;
    static int dp[maxn];
    scanf("%d%d%d", &n, &m, &k);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        dp[i] = (dp[i - 1] + 1) % mod;
        for(int j = i - 1; j > 0; --j)
            dp[j] = (dp[j - 1] + dp[j]) * (i64)inv2 % mod;
    }
    int ans = (i64)dp[m] * k % mod;
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