class Solution {
public:
    string shortestCommonSupersequence(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<int> > dp(n + 1, vector<int>(m + 1, INT_MIN));
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j) {
                if(!i && !j) {
                    dp[i][j] = 0;
                    continue;
                }
                if(i) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                    if(j && s[i - 1] == t[j - 1])
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                }
                if(j)
                    dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        string ret = "";
        for(int i = n, j = m; !(!i && !j); ) {
            if(i) {
                if(j && s[i - 1] == t[j - 1] && dp[i][j] == dp[i - 1][j - 1] + 1) {
                    ret.push_back(s[i - 1]);
                    --i;
                    --j;
                    continue;
                }
                if(dp[i][j] == dp[i - 1][j]) {
                    ret.push_back(s[i - 1]);
                    --i;
                    continue;
                }
            }
            if(j) {
                if(dp[i][j] == dp[i][j - 1]) {
                    ret.push_back(t[j - 1]);
                    --j;
                    continue;
                }
            }
            assert(0);
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
