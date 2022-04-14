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

const int maxn = 15, maxm = (int)2e6 + 1;
const int maxd = 1 << 14 | 1, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const i64 INFLL = (i64)INF << 32 | INF;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}
inline bool is_prime(int x) {
    if(x <= 2 || !(x & 1))
        return x == 2;
    for(int i = 3; i * i <= x; i += 2)
        if(x % i == 0)
            return 0;
    return 1;
}
inline i64 mod_mul(i64 x, i64 y, i64 mod) {
    i64 ret = x * y - (i64)((f128)x * y / mod + 1e-3) * mod;
    for( ; ret < 0; ret += mod);
    return ret;
}
inline i64 mod_pow(i64 x, i64 k, i64 mod) {
    i64 ret = mod > 1 ? 1 : 0;
    for( ; k > 0; k >>= 1, x = mod_mul(x, x, mod))
        if(k & 1)
            ret = mod_mul(ret, x, mod);
    return ret;
}

int inv[maxm];
int solve() {
    int n;
    static int a[maxn], prb[maxn][maxm], f[maxm];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    int m = 1 << n;
    for(int i = 0; i < n; ++i) {
        prb[i][0] = 1;
        for(int j = 0; j < n; ++j) {
            prb[i][1 << j] = (i64)a[i] * inv[a[i] + a[j]] % mod;
            // printf("prb %d %d: %d\n", i, j, prb[i][1 << j]);
        }
        for(int j = 1; j < m; ++j) {
            int lbt = j & -j;
            if(lbt == j)
                continue;
            prb[i][j] = (i64)prb[i][j ^ lbt] * prb[i][lbt] % mod;
        }
    }
    int ans = 0;
    for(int i = 0; i < m; ++i) {
        f[i] = 1;
        for(int j = (i - 1) & i; j; j = (j - 1) & i) {
            int tmp = f[j];
            for(int k = 0; k < n; ++k)
                if(((i >> k) & 1) && !((j >> k) & 1))
                    tmp = (i64)tmp * prb[k][j] % mod;
            (f[i] -= tmp) < 0 && (f[i] += mod);
        }
        // printf("f %d: %d\n", i, f[i]);
        int tmp = f[i], cnt = 0;
        for(int j = 0; j < n; ++j)
            if((i >> j) & 1) {
                ++cnt;
                tmp = (i64)tmp * prb[j][~i & (m - 1)] % mod;
            }
        ans = (ans + (i64)tmp * cnt) % mod;
    }
    return ans;
}

int main() {
    inv[1] = 1;
    for(int i = 2; i < maxm; ++i) {
        inv[i] = mod - (int)(mod / i * (i64)inv[mod % i] % mod);
    }
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		printf("%d\n", solve());
		// solve();
	}
	return 0;
}