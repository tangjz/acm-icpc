class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        int ans = 0;
        vector<int> que = {0}, par(n, -1), sz(n);
        que.reserve(n);
        for(int i = 0; i < n; ++i) {
            int u = que[i];
            for(int v: e[u])
                if(v != par[u]) {
                    par[v] = u;
                    que.push_back(v);
                }
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = que[i], p = par[u];
            sz[u] = (sz[u] + values[u]) % k;
            ans += !sz[u];
            if(p != -1)
                (sz[p] += sz[u]) >= k && (sz[p] -= k);
        }
        return ans;
    }
};
