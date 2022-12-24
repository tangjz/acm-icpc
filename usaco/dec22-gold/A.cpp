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
    int n, A, B;
    scanf("%d%d%d", &n, &A, &B);
    vector<vector<int> > seq(n);
    for(int i = 0; i < n; ++i) {
        int w, a, b;
        scanf("%d%d%d", &w, &a, &b);
        seq[i] = {w, a, b};
    }
    sort(seq.begin(), seq.end(), [&](auto const &u, auto const &v) {
        return u[2] < v[2];
    });
    int ans = 0;
    vector<vector<int> > pre(n, vector<int>(B + 1)), suf(n, vector<int>(A + 1));
    for(int i = n - 1; i >= 0; --i) {
        int w = seq[i][0], cost = seq[i][1];
        if(i + 1 < n)
            suf[i].assign(suf[i + 1].begin(), suf[i + 1].end());
        for(int j = A; j >= cost; --j)
            suf[i][j] = max(suf[i][j], suf[i][j - cost] + w);
    }
    for(int i = 0; i < n; ++i) {
        int w = seq[i][0], a = seq[i][1], b = seq[i][2], cost = a * b;
        if(i > 0)
            pre[i].assign(pre[i - 1].begin(), pre[i - 1].end());
        for(int j = B; j >= cost; --j)
            pre[i][j] = max(pre[i][j], pre[i][j - cost] + w);
        for(int j = min(a, A), k = (a - j) * b; j >= 0 && k <= B; --j, k += b) {
            int tmp = w;
            if(i > 0)
                tmp += pre[i - 1][B - k];
            if(i + 1 < n)
                tmp += suf[i + 1][A - j];
            ans = max(ans, tmp);
        }
    }
    printf("%d\n", ans);
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