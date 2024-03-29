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

i64 solve() {
    int n;
    static int arr[2][maxn];
    scanf("%d", &n);
    arr[0][0] = arr[1][0] = 0;
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        x = x & 1;
        arr[x][++arr[x][0]] = i;
    }
    i64 ans = INFLL;
    int even = (n + 1) >> 1, odd = n - even;
    for(int i = 0; i < 2; ++i) {
        if(arr[i][0] != even || arr[!i][0] != odd)
            continue;
        i64 tmp = 0;
        for(int j = 0; j < arr[i][0]; ++j)
            tmp += abs((j << 1) - arr[i][j + 1]);
        for(int j = 0; j < arr[!i][0]; ++j)
            tmp += abs((j << 1 | 1) - arr[!i][j + 1]);
        ans = min(ans, tmp);
    }
    return ans < INFLL ? (ans >> 1) : -1;
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		printf("%lld\n", solve());
		// solve();
	}
	return 0;
}
