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
    vector<int> ord(n), par(n, -1), deg(n);
    vector<LL> s(n);
    vector<vector<pair<int, LL> > > e(n);
    LL sum = 0;
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &s[i]);
        sum += s[i];
    }
    assert(sum % n == 0);
    sum /= n;
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].push_back({--v, 0LL});
        e[v].push_back({u, 0LL});
    }
    int tot = 1;
    ord[0] = 0;
    for(int i = 0; i < tot; ++i) {
        int u = ord[i];
        for(auto &it: e[u]) {
            int v = it.first;
            if(v == par[u])
                continue;
            ord[tot++] = v;
            par[v] = u;
        }
        e[u].clear();
    }
    assert(tot == n);
    int ans = 0;
    for(int i = n - 1; i >= 0; --i) {
        int u = ord[i], p = par[u];
        s[u] -= sum;
        if(p == -1 || !s[u])
            continue;
        ++ans;
        s[p] += s[u];
        if(s[u] > 0) {
            e[u].push_back({p, s[u]});
            ++deg[p];
        } else {
            e[p].push_back({u, -s[u]});
            ++deg[u];
        }
    }
    tot = 0;
    for(int i = 0; i < n; ++i)
        if(!deg[i])
            ord[tot++] = i;
    printf("%d\n", ans);
    for(int i = 0; i < tot; ++i) {
        int u = ord[i];
        for(auto &it: e[u]) {
            int v = it.first;
            LL dt = it.second;
            printf("%d %d %lld\n", u + 1, v + 1, dt);
            if(!(--deg[v]))
                ord[tot++] = v;
        }
    }
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
