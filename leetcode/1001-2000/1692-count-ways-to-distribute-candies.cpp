class Solution {
public:
    int waysToDistribute(int n, int k) {
        typedef long long LL;
        static const int maxn = (int)1e3 + 1, mod = (int)1e9 + 7;
        static int dp[maxn];
        memset(dp, 0, (k + 1) * sizeof(int));
        dp[0] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = min(i, k); j > 0; --j)
                dp[j] = ((LL)j * dp[j] + dp[j - 1]) % mod;
            dp[0] = 0;
        }
        return dp[k];
    }
};
