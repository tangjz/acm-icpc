class Solution {
public:
    int numberOfWays(int numPeople) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = numPeople / 2;
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 0; j < i; ++j)
                dp[i] = (dp[i] + (LL)dp[j] * dp[i - 1 - j]) % mod;
        return dp.back();
    }
};
