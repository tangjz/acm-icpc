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
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> deg(n), ord(n), rnk(n), dsu(n, -1);
    vector<vector<int> > e(n);
    vector<set<pair<int, int> > > sp(n);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[--u].push_back(--v);
        e[v].push_back(u);
    }
    set<pair<int, int> > ssp;
    for(int i = 0; i < n; ++i) {
        deg[i] = e[i].size();
        ssp.insert({deg[i], i});
    }
    int tot = 0;
    while(!ssp.empty()) {
        int u = ssp.begin() -> second;
        // printf("erase %d: %d\n", u, deg[u]);
        ord[tot++] = u;
        ssp.erase({deg[u], u});
        deg[u] = -1;
        for(int v: e[u])
            if(deg[v] != -1) {
                ssp.erase({deg[v], v});
                ssp.insert({--deg[v], v});
            }
    }
    assert(tot == n);
    reverse(ord.begin(), ord.end());
    int ans = 1;
    for(int i = 0; i < n; ++i) {
        rnk[ord[i]] = i;
        deg[i] = 0;
        sp[i].insert({0, i});
    }
    function<int(int)> dsuFind = [&](int x) {
        return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
    };
    auto dsuMerge = [&](int x, int y) {
        int u = dsuFind(x), v = dsuFind(y);
        // printf("add %d %d\n", x, y);
        if(u == v) {
            sp[u].erase({deg[x], x});
            sp[u].erase({deg[y], y});
            sp[u].insert({++deg[x], x});
            sp[u].insert({++deg[y], y});
            return;
        }
        if(dsu[u] > dsu[v]) {
            swap(u, v);
            swap(x, y);
        }
        dsu[u] += dsu[v];
        dsu[v] = u;
        sp[u].erase({deg[x], x});
        sp[v].erase({deg[y], y});
        if(sp[u].size() < sp[v].size())
            sp[u].swap(sp[v]);
        sp[u].insert(sp[v].begin(), sp[v].end());
        sp[v].clear();
        sp[u].insert({++deg[x], x});
        sp[u].insert({++deg[y], y});
    };
    // pair<int, vector<int> > las = {e[ord[0]].size(), {}};
    auto upd = [&](int u) {
        int p = dsuFind(u);
        // printf("check %d: %d (%d, %d)\n", u, -dsu[p], sp[p].begin() -> first, sp[p].begin() -> second);
        ans = max(ans, -dsu[p] * (sp[p].begin() -> first));
    };
    for(int u: ord) {
        // printf("new node %d: deg %d rnk %d\n", u, (int)e[u].size(), rnk[u]);
        // if(las.first != e[u].size()) {
        //     for(int v: las.second)
        //         upd(v);
        //     las = {e[u].size(), {u}};
        // } else {
        //     las.second.push_back(u);
        // }
        for(int v: e[u])
            if(rnk[v] < rnk[u])
                dsuMerge(u, v);
        upd(u);
    }
    // for(int v: las.second)
    //     upd(v);
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
