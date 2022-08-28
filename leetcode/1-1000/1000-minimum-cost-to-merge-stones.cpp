class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if((n - 1) % (k - 1) > 0)
            return -1;
        const int INF = (int)1e9;
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(n, vector<int>(k, INF)));
        for(int i = 0; i < n; ++i)
            dp[i][i][0] = 0;
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                int sum = 0;
                for(int M = L; M < R; ++M) {
                    sum += stones[M];
                    for(int i = 0; i < k; ++i) {
                        dp[L][R][i] = min(dp[L][R][i], dp[L][M][0] + dp[M + 1][R][(i + 1) % (k - 1)]);
                    }
                }
                sum += stones[R];
                dp[L][R][0] = min(dp[L][R][0] + sum, INF);
                // printf("dp[%d][%d][0]=%d\n", L, R, dp[L][R][0]);
            }
        return dp[0][n - 1][0];
    }
};
