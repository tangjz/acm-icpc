#include <bits/stdc++.h>
using namespace std;

typedef unsigned UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;

const int maxn = (int)2e5 + 9, mod = (int)1e9 + 7;
const int maxd = 10, maxc = 26, INF = 0x3f3f3f3f;
const LL maxv = (LL)1e18, INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void prepare() {
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    vector<vector<int> > e(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            scanf("%d", &e[i][j]);
    for(int i = n - 2; i >= 0; --i) {
        if(!e[i][i + 1]) {
            a[i] = a[i + 1];
            continue;
        }
        int j = i + 2;
        for( ; j < n && e[i][j] > e[i + 1][j]; ++j);
        // printf("%d: j %d\n", i, j);
        if(j < n) {
            int L = a[i + 1], R = L;
            for(int k = i + 2; k < j; ++k)
                if(a[k] < L) {
                    L = a[k];
                } else if(a[k] > R) {
                    R = a[k];
                }
            int adt = e[i][j - 1] - e[i + 1][j - 1];
            if(a[j] < L) {
                a[i] = L - adt;
            } else if(a[j] > R) {
                a[i] = R + adt;
            } else {
                assert(0);
            }
            continue;
        }
        if(i == n - 2) {
            a[i] = a[i + 1] + e[i][i + 1];
            continue;
        }
        vector<int> cand = {a[i + 1] + e[i][i + 1], a[i + 1] - e[i][i + 1]};
        for(int v: cand) {
            bool skp = 0;
            int L = v, R = v;
            for(int k = i + 1; !skp && k < n; ++k) {
                if(a[k] < L) {
                    L = a[k];
                } else if(a[k] > R) {
                    R = a[k];
                }
                skp |= R - L != e[i][k];
            }
            if(!skp) {
                a[i] = v;
                break;
            }
        }
    }
    for(int i = 0; i < n; ++i)
        printf("%d%c", a[i], " \n"[i == n - 1]);
}

int main() {
    prepare();

    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
