class Solution {
public:
    int racecar(int target) {
        int mx = 0;
        for( ; (1 << mx) <= target; ++mx);
        vector<vector<int> > dp(target + 1, vector<int>(mx));
        for(int i = 1, j; i <= target; ++i) {
            dp[i][0] = INT_MAX;
            for(j = 1; (1 << j) - 1 < i; ++j)
                dp[i][0] = min(dp[i][0], j + 2 + dp[i - (1 << j) + 1][j - 1]);
            dp[i][0] = min(dp[i][0], j + ((1 << j) - 1 == i ? 0 : 1 + dp[(1 << j) - 1 - i][0]));
            for(j = 1; (1 << j) - 1 < i; ++j)
                dp[i - (1 << j) + 1][j] = min(dp[i - (1 << j) + 1][j - 1], j + dp[i][0]);
        }
        return dp[target][0];
    }
};
