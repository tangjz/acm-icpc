#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9;
const int maxc = 26, maxd = 10;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
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
    int n, k;
    scanf("%d%d", &n, &k);
    int mx = 1;
    static int pos[maxn][2];
    pos[0][0] = pos[0][1] = 0;
    auto upd = [&](int arr[2], int x) -> void {
        if(x > arr[0]) {
            swap(x, arr[0]);
        }
        if(x > arr[1]) {
            swap(x, arr[1]);
        }
    };
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        for( ; mx <= x; mx <<= 1)
            memset(pos + mx, 0, mx * sizeof(pos[0]));
        upd(pos[x], i);
    }
    for(int i = 1; i < mx; i <<= 1)
        for(int j = 0; j < mx; ++j) {
            if(i & j)
                continue;
            upd(pos[i | j], pos[j][0]);
            upd(pos[i | j], pos[j][1]);
        }
    LL ans = (LL)-k * mx;
    for(int i = 0; i < mx; ++i)
        if(pos[i][1] > 0) {
            // printf("%d: %d %d\n", i, pos[i][0], pos[i][1]);
            ans = max(ans, (LL)pos[i][0] * pos[i][1] - (LL)k * i);
        }
    printf("%lld\n", ans);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}