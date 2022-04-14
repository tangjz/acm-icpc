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

const int maxn = (int)1e5 + 1, maxm = (int)2e6 + 1;
const int maxd = 10, maxc = 26;
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

inline int get(int u, int v) {
    int x, y;
    printf("and %d %d\n", u, v);
    fflush(stdout);
    scanf("%d", &x);
    printf("or %d %d\n", u, v);
    fflush(stdout);
    scanf("%d", &y);
    return x + y;
}
inline void put(int x) {
    printf("finish %d\n", x);
    fflush(stdout);
}

void solve() {
    int n, k;
    scanf("%d%d", &n, &k);
    int xy = get(1, 2), yz = get(2, 3), xz = get(1, 3);
    i64 xyz = ((i64)xy + yz + xz) / 2;
    static int a[maxn];
    a[1] = xyz - yz;
    a[2] = xyz - xz;
    a[3] = xyz - xy;
    for(int i = 4; i <= n; ++i) {
        int pq = get(i - 1, i);
        a[i] = pq - a[i - 1];
    }
    sort(a + 1, a + n + 1);
    put(a[k]);
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