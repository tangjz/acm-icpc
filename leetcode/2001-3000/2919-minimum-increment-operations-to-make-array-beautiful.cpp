class Solution {
public:
    long long minIncrementOperations(vector<int>& A, int k) {
        typedef long long LL;
        const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
        int n = A.size();
        LL ans = INFLL;
        vector<LL> dp(n, INFLL);
        for(int i = 0; i < n; ++i) {
            if(i < 3)
                dp[i] = min(dp[i], (LL)max(k - A[i], 0));
            for(int j = 1; j <= 3 && j <= i; ++j)
                dp[i] = min(dp[i], max(k - A[i], 0) + dp[i - j]);
            if(i >= n - 3)
                ans = min(ans, dp[i]);
        }
        return ans;
    }
};
