class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        const int maxn = 100;
        vector<int> deg(n);
        vector<vector<bool> > e(n, vector<bool>(n));
        for(auto &it: roads) {
            int u = it[0], v = it[1];
            e[u][v] = e[v][u] = 1;
            ++deg[u];
            ++deg[v];
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                ans = max(ans, deg[i] + deg[j] - e[i][j]);
        return ans;
    }
};
