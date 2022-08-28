class Solution {
public:
    int checkRecord(int n) { // (1 + x + x^2) / (1 - x - x^2 - x^3)^2
        const int mod = (int)1e9 + 7;
        vector<int> dp(n + 1);
        for(int i = 0; i < 3 && i <= n; ++i)
            dp[i] = 1;
        for(int i = 0; i <= n; ++i)
            for(int j = 1; j <= 3 && j <= i; ++j)
                (dp[i] += dp[i - j]) >= mod && (dp[i] -= mod);
        for(int i = 0; i <= n; ++i)
            for(int j = 1; j <= 3 && j <= i; ++j)
                (dp[i] += dp[i - j]) >= mod && (dp[i] -= mod);
        return dp[n];
    }
};
