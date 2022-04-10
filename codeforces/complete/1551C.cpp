#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9, maxd = 5;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n;
    scanf("%d", &n);

    vector<vector<int> > ctr(n, vector<int>(maxd + 1));
    for(int i = 0; i < n; ++i) {
        static char buf[maxn];
        scanf("%s", buf);
        for(int j = 0; buf[j]; ++j) {
            ++ctr[i][maxd];
            ++ctr[i][(int)(buf[j] - 'a')];
        }
    }

    int ans = 0;
    for(int i = 0; i < maxd; ++i) {
        vector<int> seq;
        for(int j = 0; j < n; ++j)
            seq.push_back(ctr[j][maxd] - ctr[j][i] - ctr[j][i]);
        sort(seq.begin(), seq.end());
        // printf("#%d:", i);
        for(int j = 0, s = 0; j < n; ++j) {
            // printf(" %d", seq[j]);
            s += seq[j];
            if(s < 0)
                ans = max(ans, j + 1);
        }
        // printf(": %d\n", ans);
    }
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