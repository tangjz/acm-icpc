class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        const int mod = (int)1e9 + 7;
        int m = rollMax.size();
        vector<vector<int> > dp(n + 1, vector<int>(m + 1));
        dp[0][m] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j < m; ++j) {
                dp[i][j] = dp[i - 1][m];
                if(i > rollMax[j]) {
                    (dp[i][j] -= dp[i - 1 - rollMax[j]][m]) < 0 && (dp[i][j] += mod);
                    (dp[i][j] += dp[i - 1 - rollMax[j]][j]) >= mod && (dp[i][j] -= mod);
                }
                (dp[i][m] += dp[i][j]) >= mod && (dp[i][m] -= mod);
            }
        }
        return dp[n][m];
    }
};
