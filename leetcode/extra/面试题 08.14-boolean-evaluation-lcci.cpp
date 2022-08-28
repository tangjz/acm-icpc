class Solution {
public:
    int countEval(string s, int result) {
        typedef long long LL;
        int n = (s.size() + 1) / 2;
        vector<vector<vector<LL> > > dp(n, vector<vector<LL> >(n, vector<LL>(2)));
        for(int i = 0; i < n; ++i) {
            int x = s[i << 1] == '1';
            dp[i][i] = {!x, x};
        }
        static int trA[2][2] = {
            {0, 0},
            {0, 1},
        }, trO[2][2] = {
            {0, 1},
            {1, 1},
        }, trX[2][2] = {
            {0, 1},
            {1, 0},
        };
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R)
                for(int M = L; M < R; ++M) {
                    int (*tr)[2] = s[M << 1 | 1] == '&' ? trA : (s[M << 1 | 1] == '|' ? trO : trX);
                    for(int lft = 0; lft < 2; ++lft)
                        for(int rht = 0; rht < 2; ++rht)
                            dp[L][R][tr[lft][rht]] += dp[L][M][lft] * dp[M + 1][R][rht];
                }
        return dp[0][n - 1][result];
    }
};
