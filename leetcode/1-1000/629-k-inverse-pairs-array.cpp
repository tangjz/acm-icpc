class Solution {
public:
    int kInversePairs(int n, int k) {
        static const int maxn = (int)1e3 + 1, mod = (int)1e9 + 7;
        static int dp[maxn][maxn] = {};
        if(!dp[1][0]) {
            for(int i = 0; i < maxn; ++i)
                dp[1][i] = 1;
            for(int i = 2; i < maxn; ++i) {
                dp[i][0] = 1;
                for(int j = 1; j < maxn; ++j) {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - (j < i ? 0 : dp[i - 1][j - i]);
                    if(dp[i][j] >= mod) {
                        dp[i][j] -= mod;
                    } else if(dp[i][j] < 0) {
                        dp[i][j] += mod;
                    }
                }
            }
        }
        int ans = k ? dp[n][k] - dp[n][k - 1] : 1;
        return ans < 0 ? ans + mod : ans;
    }
};
