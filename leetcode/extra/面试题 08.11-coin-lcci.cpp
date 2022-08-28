class Solution {
public:
    int waysToChange(int n) {
        static const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
        static int dp[maxn] = {};
        if(!dp[0]) {
            for(int i = 0; i < maxn; ++i)
                dp[i] = 1;
            for(int i = 5; i < maxn; ++i)
                (dp[i] += dp[i - 5]) >= mod && (dp[i] -= mod);
            for(int i = 10; i < maxn; ++i)
                (dp[i] += dp[i - 10]) >= mod && (dp[i] -= mod);
            for(int i = 25; i < maxn; ++i)
                (dp[i] += dp[i - 25]) >= mod && (dp[i] -= mod);
        }
        return dp[n];
    }
};
