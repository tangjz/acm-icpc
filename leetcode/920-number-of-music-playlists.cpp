class Solution {
public:
    int numMusicPlaylists(int m, int n, int k) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7;
        vector<vector<int> > dp(n + 1, vector<int>(m + 1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                dp[i][j] = (m - j + 1LL) * dp[i - 1][j - 1] % mod;
                if(j > k)
                    dp[i][j] = (dp[i][j] + (LL)(j - k) * dp[i - 1][j]) % mod;
                // if(dp[i][j])
                //     printf("%d %d: %d\n", i, j, dp[i][j]);
            }
        return dp[n][m];
    }
};
