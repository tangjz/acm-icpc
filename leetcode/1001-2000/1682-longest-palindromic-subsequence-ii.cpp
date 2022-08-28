class Solution {
public:
    int longestPalindromeSubseq(string s) {
        static const int maxd = 26;
        int n = s.size();
        vector<vector<vector<int> > > dp(n, vector<vector<int> >(n, vector<int>(maxd)));
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                for(int i = 0; i < maxd; ++i)
                    dp[L][R][i] = max(dp[L + 1][R][i], dp[L][R - 1][i]);
                if(s[L] != s[R])
                    continue;
                int o = s[L] - 'a', best = 0;
                if(L + 1 < R - 1)
                    for(int i = 0; i < maxd; ++i)
                        if(i != o)
                            best = max(best, dp[L + 1][R - 1][i]);
                dp[L][R][o] = max(dp[L][R][o], best + 2);
            }
        return *max_element(dp[0][n - 1].begin(), dp[0][n - 1].end());
    }
};
