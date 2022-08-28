#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)2e3 + 1, mod = (int)1e9 + 7;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> lev(n + 1), ord(n + 1);
    vector<vector<int> > e(n + 1);
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &lev[i]);
        ord[i] = i;
    }
    sort(ord.begin() + 1, ord.end(), [&](int const &u, int const &v) {
        return lev[u] < lev[v];
    });
    int ans = 0;
    vector<bool> visible(n + 1);
    function<int(int, int)> dfs = [&](int u, int p) -> int {
        int ans = 1;
        for(int v: e[u])
            if(v != p && visible[v])
                ans = ans * (1LL + dfs(v, u)) % mod;
        return ans;
    };
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n && lev[ord[j]] <= lev[ord[i]] + m; ++j)
            visible[ord[j]] = 1;
        (ans += dfs(ord[i], -1)) >= mod && (ans -= mod);
        for(int j = i; j <= n && lev[ord[j]] <= lev[ord[i]] + m; ++j)
            visible[ord[j]] = 0;
    }
    printf("%d\n", ans);
    return 0;
}
