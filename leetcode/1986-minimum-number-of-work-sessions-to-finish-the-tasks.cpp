class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size(), m = 1 << n;
        vector<int> cost(m), dp(m, n);
        dp[0] = 0;
        for(int i = 1; i < m; ++i) {
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    cost[i] = cost[i ^ (1 << j)] + tasks[j];
                    break;
                }
            for(int j = i; j; j = (j - 1) & i) {
                int k = i ^ j;
                if(cost[i] - cost[k] <= sessionTime)
                    dp[i] = min(dp[i], dp[k] + 1);
            }
        }
        return dp[m - 1];
    }
};
