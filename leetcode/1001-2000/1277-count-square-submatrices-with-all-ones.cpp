class Solution {
public:
    int countSquares(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size(), ans = 0;
        vector<int> dp(m + 1, 0);
        for(int i = 1; i <= n; ++i) {
            int las = dp[0], cur;
            for(int j = 1; j <= m; ++j) {
                cur = dp[j];
                if(mat[i - 1][j - 1] == 0) {
                    dp[j] = 0;
                } else {
                    dp[j] = min(dp[j], min(dp[j - 1], las)) + 1;
                }
                ans += dp[j];
                las = cur;
            }
        }
        return ans;
    }
};
