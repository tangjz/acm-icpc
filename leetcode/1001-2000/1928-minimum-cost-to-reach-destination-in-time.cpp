class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        const int INF = 0x3f3f3f3f;
        int n = passingFees.size();
        vector<vector<int> > dp(maxTime + 1, vector<int>(n, INF));
        dp[0][0] = passingFees[0];
        int ans = INF;
        for(int i = 0; i <= maxTime; ++i) {
            ans = min(ans, dp[i][n - 1]);
            for(auto &it: edges) {
                int u = it[0], v = it[1], w = it[2];
                if(i + w <= maxTime) {
                    dp[i + w][u] = min(dp[i + w][u], dp[i][v] + passingFees[u]);
                    dp[i + w][v] = min(dp[i + w][v], dp[i][u] + passingFees[v]);
                }
            }
        }
        return ans < INF ? ans : -1;
    }
};
