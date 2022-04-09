#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int dsuFind(int dsu[], int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu, dsu[x]));
}

void solve() {
    int n, m;
    static int deg[maxn], dsu[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        deg[i] = 1;
        dsu[i] = -1;
    }
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++deg[--u];
        ++deg[--v];
        u = dsuFind(dsu, u);
        v = dsuFind(dsu, v);
        --dsu[u];
        --dsu[v];
        if(u == v)
            continue;
        if(dsu[u] < dsu[v])
            swap(u, v);
        dsu[v] += dsu[u];
        dsu[u] = v;
    }
    for(int i = 0; i < n; ++i) {
        int j = dsuFind(dsu, i), com = gcd(deg[i], -dsu[j]);
        printf("%d %d\n", -dsu[j] / com, deg[i] / com);
    }
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
