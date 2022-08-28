class Solution {
public:
    bool isValidPalindrome(string s, int k) {
        int n = s.size();
        vector<vector<int> > dp(n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            if(i + 1 < n)
                dp[i][i + 1] = 1 + (s[i] == s[i + 1]);
        }
        for(int len = 3; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                dp[L][R] = max(dp[L][R - 1], dp[L + 1][R]);
                if(s[L] == s[R])
                    dp[L][R] = max(dp[L][R], dp[L + 1][R - 1] + 2);
            }
        return dp[0][n - 1] >= n - k;
    }
};
