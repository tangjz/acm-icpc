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
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f, inv2 = (mod + 1) >> 1;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if(!k || !m) {
        puts("0");
        return;
    }
    --m;
    static int inv[maxn];
    inv[1] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = mod - (int)(mod / i * (i64)inv[mod % i] % mod);
    int coe = 1;
    for(int i = 1; i <= m; ++i)
        coe = (i64)coe * (n + 1 - i) % mod * inv[i] % mod;
    int ans = coe;
    for(int i = 1, prd = inv2; i <= m; ++i) {
        coe = (i64)coe * inv[n + 1 - i] % mod * (m + 1 - i) % mod;
        ans = (ans + (i + 3LL) * prd % mod * coe) % mod;
        prd = 2LL * prd % mod;
    }
    for(int i = 1; i < n; ++i)
        ans = (i64)ans * inv2 % mod;
    ans = (i64)ans * k % mod;
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