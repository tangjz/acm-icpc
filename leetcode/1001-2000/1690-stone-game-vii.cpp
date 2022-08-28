class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<vector<int> > dp(n, vector<int>(n));
        for(int i = 0; i < n; ++i)
            dp[i][i] = n & 1 ? 0 : stones[i];
        for(int k = 2; k <= n; ++k)
            if((n & 1) == (k & 1)) {
                for(int i = 0, j = k - 1; j < n; ++i, ++j) {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]); 
                }
            } else {
                for(int i = 0, j = k - 1; j < n; ++i, ++j) {
                    dp[i][j] = min(dp[i + 1][j] + stones[i], dp[i][j - 1] + stones[j]);
                }
            }
        return dp[0][n - 1];
    }
};
