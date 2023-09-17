class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        typedef long long LL;
        vector<int> par(n, -1), dep(n), ord(n), w(n);
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        ord[0] = 0;
        for(int i = 0, tot = 1; i < tot; ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(v != par[u]) {
                    dep[v] = dep[u] + 1;
                    par[v] = u;
                    ord[tot++] = v;
                }
        }
        for(auto &it: trips) {
            int u = it[0], v = it[1];
            while(u != v) {
                if(dep[u] < dep[v])
                    swap(u, v);
                ++w[u];
                u = par[u];
            }
            ++w[u];
        }
        vector<pair<LL, LL> > dp(n);
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], p = price[u], q = p >> 1;
            dp[u] = {(LL)q * w[u], (LL)p * w[u]};
            for(int v: e[u]) {
                if(v == par[u])
                    continue;
                LL fir = dp[u].first + dp[v].second;
                LL sec = dp[u].second + min(dp[v].first, dp[v].second);
                dp[u] = {fir, sec};
            }
        }
        return min(dp[0].first, dp[0].second);
    }
};
