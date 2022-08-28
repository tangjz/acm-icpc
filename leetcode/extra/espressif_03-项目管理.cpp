#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

int main() {
    int n, m;
    scanf("%d", &n);
    vector<int> adt(n), dp(n, -1);
    vector<vector<int> > e(n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &adt[i]);
    scanf("%d", &m);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[v].push_back(u);
    }
    function<int(int)> calc = [&](int u) -> int {
        if(dp[u] >= 0)
            return dp[u];
        if(dp[u] == -2)
            return INT_MAX;
        dp[u] = -2;
        int upp = 0;
        for(int v: e[u])
            upp = max(upp, calc(v));
        return dp[u] = upp + adt[u];
    };
    int ans = 0;
    for(int i = 0; i < n; ++i)
        ans = max(ans, calc(i));
    printf("%d\n", ans);
    return 0;
}
