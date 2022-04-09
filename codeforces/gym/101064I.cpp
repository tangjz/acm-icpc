#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e4 + 1;

bool dfs(int u, int p, vector<vector<int> > &e, vector<int> &tim, int &tot) {
    tim[u] = ++tot;
    int las = -1;
    for(int v: e[u]) {
        if(v == p || tim[v] > tim[u] || (!tim[v] && dfs(v, u, e, tim, tot)))
            continue;
        if(las == -1) {
            las = v;
        } else {
            printf("%d %d %d\n", las + 1, u + 1, v + 1);
            las = -1;
        }
    }
    if(las != -1) {
        printf("%d %d %d\n", las + 1, u + 1, p + 1);
        return 1;
    }
    return 0;
}

void solve() {
    int n, m, tot = 0;
    scanf("%d%d", &n, &m);
    vector<int> tim(n);
    vector<vector<int> > e(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    m >>= 1;
    printf("%d\n", m);
    dfs(0, -1, e, tim, tot);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}