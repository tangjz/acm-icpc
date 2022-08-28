class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<int> dp(n);
        for(int i = 0; i < n; ++i) {
            char ch = s[n - 1 - i];
            int las = 0, cur;
            for(int j = 0; j < n; ++j) {
                cur = dp[j];
                dp[j] = s[j] == ch ? las + 1 : (j > 0 ? max(dp[j - 1], cur) : cur);
                las = cur;
            }
        }
        return dp.back();
    }
};
