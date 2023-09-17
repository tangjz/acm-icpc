class Solution {
public:
    int numberOfWays(int n, int x) {
        static const int mod = (int)1e9 + 7;
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 1; ; ++i) {
            int v = 1;
            for(int j = 0; j < x && v <= n; ++j)
                v *= i;
            if(v > n)
                break;
            for(int j = n; j >= v; --j)
                (dp[j] += dp[j - v]) >= mod && (dp[j] -= mod);
        }
        return dp[n];
    }
};
