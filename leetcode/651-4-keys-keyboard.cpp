class Solution {
public:
    int maxA(int n) {
        vector<int> dp(n + 1);
        for(int i = 1; i <= n; ++i)
            dp[i] = i < 6 ? i : max(dp[i - 4] * 3, dp[i - 5] * 4);
        return dp[n];
    }
};
