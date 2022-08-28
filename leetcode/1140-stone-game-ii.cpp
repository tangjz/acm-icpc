class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<vector<int> > > dp(2, vector<vector<int> >(n + 1, vector<int>(n + 1)));
        for(int i = n - 1; i >= 0; --i)
            for(int j = 1; j <= n; ++j) {
                int s = 0;
                // dp[0][i][j] = max(dp[1][i + k][max(j, k)] + sum[i:i+k])
                // dp[1][i][j] = min(dp[0][i + k][max(j, k)])
                dp[0][i][j] = INT_MIN;
                dp[1][i][j] = INT_MAX;
                for(int k = 1; i + k <= n && k <= j + j; ++k) {
                    s += piles[i + k - 1];
                    dp[0][i][j] = max(dp[0][i][j], dp[1][i + k][max(j, k)] + s);
                    dp[1][i][j] = min(dp[1][i][j], dp[0][i + k][max(j, k)]);
                }
            }
        return dp[0][0][1];
    }
};
