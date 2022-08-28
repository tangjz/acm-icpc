class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<unsigned int> > dp(n + 1, vector<unsigned int>(m + 1));
        dp[0][0] = 1;
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j) {
                if(i > 0) {
                    dp[i][j] += dp[i - 1][j];
                    if(i > 0 && j > 0 && s[i - 1] == t[j - 1])
                        dp[i][j] += dp[i - 1][j - 1];
                }
            }
        return dp[n][m];
    }
};
