#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e3 + 9, maxm = (int)1e6 + 9;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    static int a[maxn], b[maxn];
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        b[i] = i + 1 - a[i];
    }
    int ans = INF;
    static bitset<maxn> dp[maxn];
    for(int i = 0; i < n; ++i) {
        dp[i].reset();
        // printf("%d: %d %d\n", i, a[i], b[i]);
        if(b[i] < 0)
            continue;
        dp[i].set(1);
        for(int j = 0; j < i; ++j)
            if(a[j] < a[i] && b[j] <= b[i]) {
                // printf("%d -> %d\n", j, i);
                dp[i] |= dp[j] << 1;
            }
        if(dp[i].test(m))
            ans = min(ans, b[i]);
    }
    printf("%d\n", ans < INF ? ans : -1);
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