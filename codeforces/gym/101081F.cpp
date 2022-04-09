#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

void solve() {
    int n, m;
    static int dsu[maxn], up[maxn];
    vector<vector<int> > edges;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        dsu[i] = -1;
    while(m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges.push_back({w, u, v});
    }
    sort(edges.begin(), edges.end());
    for(auto &it: edges) {
        int u = it[1], v = it[2], w = it[0];
        for( ; dsu[u] > 0; u = dsu[u]);
        for( ; dsu[v] > 0; v = dsu[v]);
        if(u == v)
            continue;
        if(dsu[u] < dsu[v])
            swap(u, v);
        dsu[v] -= dsu[u] == dsu[v];
        dsu[u] = v;
        up[u] = w;
    }
    scanf("%d", &m);
    while(m--) {
        vector<int> f[2];
        for(int i = 0; i < 2; ++i) {
            int x;
            scanf("%d", &x);
            for( ; dsu[x] > 0; x = dsu[x])
                f[i].push_back(x);
        }
        while(!f[0].empty() && !f[1].empty() && f[0].back() == f[1].back()) {
            f[0].pop_back();
            f[1].pop_back();
        }
        int ans = 0;
        if(!f[0].empty())
            ans = max(ans, up[f[0].back()]);
        if(!f[1].empty())
            ans = max(ans, up[f[1].back()]);
        printf("%d\n", ans);
    }
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
