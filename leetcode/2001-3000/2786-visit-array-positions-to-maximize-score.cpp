class Solution {
public:
    long long maxScore(vector<int>& A, int x) {
        typedef long long LL;
        const LL INF = 0x3f3f3f3f3f3f3f3fLL;
        int n = A.size();
        LL dp[2] = {-INF, -INF};
        int o = A[0] & 1;
        dp[o] = A[0];
        for(int i = 1; i < n; ++i) {
            int o = A[i] & 1;
            dp[o] = max(dp[o], max(dp[o], dp[!o] - x) + A[i]);
        }
        return max(dp[0], dp[1]);
    }
};
