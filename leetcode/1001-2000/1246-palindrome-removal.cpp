class Solution {
public:
    int minimumMoves(vector<int>& arr) {
        const int maxn = 101, INF = 0x3f3f3f3f;
        int n = arr.size();
        static int dp[2][maxn][maxn];
        for(int len = 1; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                dp[0][L][R] = dp[1][L][R] = INF;
                if(arr[L] == arr[R]) {
                    int nxt = len > 2 ? dp[1][L + 1][R - 1] : 0;
                    dp[0][L][R] = min(dp[0][L][R], nxt + 1);
                    dp[1][L][R] = min(dp[1][L][R], nxt);
                }
                for(int M = L; M < R; ++M) {
                    dp[0][L][R] = min(dp[0][L][R], dp[0][L][M] + dp[0][M + 1][R]);
                    dp[1][L][R] = min(dp[1][L][R], min(dp[1][L][M] + dp[0][M + 1][R], dp[0][L][M] + dp[1][M + 1][R]));
                }
            }
        return dp[0][0][n - 1];
    }
};
