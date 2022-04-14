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
    int n, m = 0;
    static int a[maxn];
    static pair<int, int> stk[maxn];
    static i64 dp[maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    i64 cnt = 0;
    i64 ans = 0;
    dp[0] = 0;
    for(int i = 2; i <= n; i += 2) {
        int dif = a[i] - a[i - 1];
        if(dif > 0) {
            dp[i] = cnt >= dif;
            ans += dp[i - 2] + min(cnt, (i64)dif);
            i64 tmp = 0;
            while(m > 0) {
                int j, rem;
                tie(j, rem) = stk[--m];
                tmp += rem;
                if(tmp <= dif) {
                    ans += dp[j - 2];
                    if(tmp == dif)
                        dp[i] += dp[j - 2];
                } else {
                    stk[m++] = {j, (int)(tmp - dif)};
                    break;
                }
            }
        } else if(dif < 0) {
            dp[i] = 1;
            stk[m++] = {i, -dif};
        } else {
            dp[i] = 1 + dp[i - 2];
            ans += dp[i - 2];
        }
        ans += min(a[i], a[i - 1]);
        cnt = max(cnt - dif, 0LL);
        // printf("%d: %lld (%lld, %lld)\n", i, dp[i], cnt, ans);
    }
    return ans;
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		printf("%lld\n", solve());
		// solve();
	}
	return 0;
}