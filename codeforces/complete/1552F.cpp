#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9;
const int maxc = 26, maxd = 10;
const int mod = 998244353, INF = 0x3f3f3f3f;
const LL INFLL = (LL)INF << 32 | INF;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
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
inline LL mod_mul(LL x, LL y, LL mod) {
    LL ret = x * y - (LL)((LD)x * y / mod + 1e-3) * mod;
    for( ; ret < 0; ret += mod);
    return ret;
}
inline LL mod_pow(LL x, LL k, LL mod) {
    LL ret = mod > 1 ? 1 : 0;
    for( ; k > 0; k >>= 1, x = mod_mul(x, x, mod))
        if(k & 1)
            ret = mod_mul(ret, x, mod);
    return ret;
}

void solve() {
    int n;
    static int L[maxn], R[maxn], s[maxn];
    scanf("%d", &n);
    static int dp[maxn], sum[maxn];
    sum[0] = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d%d", R + i, L + i, s + i);
        dp[i] = R[i] - L[i];
        if(i > 1 && L[i] < R[i - 1]) {
            int j = lower_bound(R + 1, R + i + 1, L[i]) - R;
            dp[i] = (dp[i] + sum[i - 1] - sum[j - 1]) % mod;
            dp[i] < 0 && (dp[i] += mod);
        }
        sum[i] = (sum[i - 1] + dp[i]) % mod;
        // printf("%d: %d\n", i, dp[i]);
    }
    int ans = (R[n] + 1) % mod;
    for(int i = 1; i <= n; ++i)
        if(s[i] == 1)
            (ans += dp[i]) %= mod;
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}