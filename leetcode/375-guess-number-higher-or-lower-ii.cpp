class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int> > dp(n, vector<int>(n));
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                dp[L][R] = INT_MAX;
                for(int M = L; M <= R; ++M) {
                    int cost = 0;
                    if(L < M)
                        cost = max(cost, dp[L][M - 1]);
                    if(M < R)
                        cost = max(cost, dp[M + 1][R]);
                    cost += M + 1;
                    dp[L][R] = min(dp[L][R], cost);
                }
            }
        return dp[0][n - 1];
    }
};
