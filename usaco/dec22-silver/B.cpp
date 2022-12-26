#include <bits/stdc++.h>
using namespace std;

typedef unsigned UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;

const int maxn = (int)2e5 + 9, maxv = (int)5e6 + 9, mod = (int)1e9 + 7;
const int maxd = 10, maxc = 26, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

vector<int> dp(maxv);

void prepare() {
    vector<int> pr, d(maxv), cand(4);
    cand[1] = 1;
    dp[1] = 0;
    for(int i = 2; i < maxv; ++i) {
        if(!d[i]) {
            d[i] = i;
            pr.push_back(i);
            cand[i & 3] = i;
        }
        dp[i] = (i & 1 ? i - cand[i & 3] : i) >> 2;
        for(int p: pr) {
            int j = i * p;
            if(j >= maxv)
                break;
            d[j] = p;
            if(d[i] == p)
                break;
        }
    }
}

void solve() {
    int n;
    pair<int, int> best = {INT_MAX, INT_MAX};
    scanf("%d", &n);
    for(int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        if(dp[x] < best.first)
            best = {dp[x], x};
    }
    puts(best.second & 3 ? "Farmer John" : "Farmer Nhoj");
}

int main() {
    prepare();

    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
