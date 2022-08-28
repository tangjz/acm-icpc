class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        typedef long long LL;
        int n = arr.size();
        vector<vector<LL> > dp(n, vector<LL>(n, LLONG_MAX)), cost(n, vector<LL>(n));
        for(int i = 0; i < n; ++i) {
            dp[i][i] = 0;
            cost[i][i] = arr[i];
        }
        for(int i = 2; i <= n; ++i)
            for(int L = 0, R = i - 1; R < n; ++L, ++R) {
                cost[L][R] = max(cost[L][R - 1], (LL)arr[R]);
                for(int M = L; M < R; ++M)
                    dp[L][R] = min(dp[L][R], dp[L][M] + dp[M + 1][R] + cost[L][M] * cost[M + 1][R]);
            }
        return dp[0][n - 1];
    }
};
