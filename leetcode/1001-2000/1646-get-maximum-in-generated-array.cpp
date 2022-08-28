class Solution {
public:
    int getMaximumGenerated(int n) {
        int ans = 0;
        vector<int> dp(n + 1);
        for(int i = 0; i <= n; ++i) {
            if(i <= 1) {
                dp[i] = i;
            } else if(i & 1) {
                dp[i] = dp[i >> 1] + dp[(i + 1) >> 1];
            } else {
                dp[i] = dp[i >> 1];
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
