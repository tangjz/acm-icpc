class Solution {
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        typedef long long LL;
        vector<vector<LL> > dp(m + 1, vector<LL>(n + 1));
        for(auto &it: prices)
            dp[it[0]][it[1]] = max(dp[it[0]][it[1]], (LL)it[2]);
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j) {
                for(int k = 1; k < i; ++k)
                    dp[i][j] = max(dp[i][j], dp[k][j] + dp[i - k][j]);
                for(int k = 1; k < j; ++k)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        return dp[m][n];
    }
};
