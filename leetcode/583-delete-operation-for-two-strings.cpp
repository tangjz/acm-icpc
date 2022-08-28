class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = (int)word1.length();
        int len2 = (int)word2.length();
        vector<int> dp(len2 + 1, 0);
        for(int i = 1; i <= len1; ++i) {
            int las = dp[0], cur;
            for(int j = 1; j <= len2; ++j) {
                cur = dp[j];
                if(word1[i - 1] == word2[j - 1]) {
                    dp[j] = las + 1;
                } else {
                    dp[j] = max(dp[j - 1], dp[j]);
                }
                las = cur;
            }
        }
        return len1 + len2 - dp[len2] * 2;
    }
};
