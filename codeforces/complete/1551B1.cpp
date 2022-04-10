#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9, maxd = 26;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    static char buf[maxn];
    scanf("%s", buf);
    int ctr[maxd] = {};
    for(int i = 0; buf[i]; ++i)
        ++ctr[(int)(buf[i] - 'a')];
    int ans = 0;
    for(int i = 0; i < maxd; ++i)
        ans += min(ctr[i], 2);
    ans >>= 1;
    printf("%d\n", ans);
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