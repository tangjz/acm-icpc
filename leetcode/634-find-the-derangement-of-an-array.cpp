class Solution {
public:
    int findDerangement(int n) {
        typedef long long LL;
        const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7;
        static int mx = 0, dp[maxn] = {};
        if(!mx) {
            dp[0] = 1;
            mx = 2;
        }
        for( ; mx <= n; ++mx)
            dp[mx] = (mx - 1LL) * (dp[mx - 1] + dp[mx - 2]) % mod;
        return dp[n];
    }
};
