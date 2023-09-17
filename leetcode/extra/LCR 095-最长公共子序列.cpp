class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = (int)text1.length();
        int len2 = (int)text2.length();
        vector<int> dp(len2 + 1, 0);
        for(int i = 1; i <= len1; ++i) {
            int las = dp[0], cur;
            for(int j = 1; j <= len2; ++j) {
                cur = dp[j];
                if(text1[i - 1] == text2[j - 1]) {
                    dp[j] = las + 1;
                } else {
                    dp[j] = max(dp[j - 1], dp[j]);
                }
                las = cur;
            }
        }
        return dp[len2];
    }
};
