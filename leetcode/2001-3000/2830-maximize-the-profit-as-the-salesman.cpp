class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& A) {
        int m = A.size();
        vector<int> dp(n + 1);
        sort(A.begin(), A.end(), [&](auto const &u, auto const &v) {
            return u[1] < v[1];
        });
        for(int i = 0, j = 0; i < n; ++i) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            for( ; j < m && A[j][1] == i; ++j)
                dp[i + 1] = max(dp[i + 1], dp[A[j][0]] + A[j][2]);
        }
        return dp[n];
    }
};
