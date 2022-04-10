#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)1e2 + 9, maxm = (int)1e6 + 9, maxd = 26;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n, m, h;
    scanf("%d%d%d", &n, &m, &h);
    bool flip = 0;
    if(m & 1) {
        flip = 1;
        swap(n, m);
        h = n * m / 2 - h;
    }
    int sta = (n & 1) * (m >> 1);
    if(h < sta || (h - sta) & 1) {
        puts("NO");
        return;
    }
    puts("YES");
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