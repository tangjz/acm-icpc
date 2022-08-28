class Solution {
public:
    int strangePrinter(string s) {
        s.erase(unique(s.begin(), s.end()), s.end());
        int n = s.size();
        vector<vector<int> > dp(n, vector<int>(n, n));
        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                for(int M = L; M < R; ++M)
                    dp[L][R] = min(dp[L][R], dp[L][M] + dp[M + 1][R]);
                dp[L][R] -= s[L] == s[R];
            }
        return dp[0][n - 1];
    }
};
