class Solution {
public:
    int numTilings(int n) {
        vector<int> dp(max(n, 2) + 1);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        const int mod = (int)1e9 + 7;
        for(int i = 3; i <= n; ++i)
            dp[i] = (dp[i - 1] * 2LL + dp[i - 3]) % mod;
        return dp[n];
    }
};
