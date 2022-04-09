#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

void solve() {
    int n, m;
    static int rem[maxn], ord[maxn], ans[maxn], p[maxn];
    static vector<int> q[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i)
        scanf("%d", rem + i);
    for(int i = 1; i <= n; ++i) {
        int sz;
        scanf("%d%d", p + i, &sz);
        q[i].resize(sz);
        for(int j = 0; j < sz; ++j)
            scanf("%d", &q[i][j]);
        ord[i] = i;
        ans[i] = -1;
    }
    sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
        return make_pair(-p[u], u) < make_pair(-p[v], v);
    });
    for(int i = 1, j; i <= n; i = j) {
        for(j = i; j <= n && p[ord[i]] == p[ord[j]]; ++j);
        int pos = 0;
        for(bool stp = 0; !stp; ++pos) {
            stp = 1;
            for(int k = i; k < j; ++k) {
                if(pos >= q[ord[k]].size())
                    continue;
                int v = q[ord[k]][pos];
                if(rem[v]) {
                    --rem[v];
                    ans[ord[k]] = v;
                    q[ord[k]].clear();
                    continue;
                }
                stp = 0;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
