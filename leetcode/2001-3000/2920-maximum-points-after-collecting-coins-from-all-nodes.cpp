class Solution {
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& w, int k) {
        static const int maxd = 15, maxv = (int)1e5 + 1, INF = 0x3f3f3f3f;
        static int dp[maxd][maxv];
        int n = edges.size() + 1;
        vector<int> que, par(n, -1);
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
            // printf("edge: %d %d\n", it[0], it[1]);
        }
        que.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = que[i];
            for(int v: e[u])
                if(par[u] != v) {
                    par[v] = u;
                    que.push_back(v);
                }
        }
        // printf("que: %d\n", (int)que.size());
        for(int i = 0; i < maxd; ++i)
            memset(dp[i], 0, n * sizeof(int));
        for(int i = n - 1; i >= 0; --i) {
            int u = que[i], p = par[u];
            for(int j = 0; j < maxd; ++j)
                dp[j][u] = max((j + 1 < maxd ? dp[j + 1][u] : 0) + (w[u] >> (j + 1)), dp[j][u] + (w[u] >> j) - k);
            // printf("u %d: ", u);
            // for(int j = 0; j < maxd; ++j)
            //     printf("%d%c", dp[j][u], " \n"[j == maxd - 1]);
            if(p == -1)
                continue;
            for(int j = 0; j < maxd; ++j)
                dp[j][p] += dp[j][u];
        }
        return dp[0][0];
    }
};
