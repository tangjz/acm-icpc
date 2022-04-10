#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n;
    scanf("%d", &n);
    int m = n / 3;
    int best = n, c0 = n, c1 = 0;
    for(int i = max(m - 3, 0); i <= m + 3 && i <= n; ++i) {
        int j = (n - i) >> 1;
        if(i + j + j == n && abs(i - j) < best) {
            best = abs(i - j);
            c0 = i;
            c1 = j;
        }
    }
    printf("%d %d\n", c0, c1);
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