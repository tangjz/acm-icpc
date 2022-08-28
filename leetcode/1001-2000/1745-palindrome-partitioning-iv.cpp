class Solution {
public:
    bool checkPartitioning(string s) {
        int n = (int)s.size();
        vector<vector<bool> > dp(n, vector<bool>(n));
        for(int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            if(i > 0 && s[i - 1] == s[i])
                dp[i - 1][i] = 1;
        }
        for(int len = 3; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R)
                dp[L][R] = s[L] == s[R] && dp[L + 1][R - 1];
        for(int L = 1; L < n; ++L) {
            if(!dp[0][L - 1])
                continue;
            for(int R = L; R + 1 < n; ++R)
                if(dp[R + 1][n - 1] && dp[L][R])
                    return true;
        }
        return false;
    }
};
