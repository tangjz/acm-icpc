class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.size();
        vector<vector<int> > lcp(n, vector<int>(n));
        for(int i = n - 1; i >= 0; --i)
            for(int j = n - 1; j >= 0; --j)
                lcp[i][j] = text[i] == text[j] ? (max(i, j) + 1 < n ? lcp[i + 1][j + 1] : 0) + 1 : 0;
        vector<int> dp(n, -1);
        if(!(n & 1))
            dp[n >> 1] = 0;
        for(int i = (n - 1) >> 1; i >= 0; --i) {
            dp[i] = max(dp[i], 1);
            for(int j = i + 1; j <= (n >> 1); ++j) {
                if(lcp[i][n - j] >= j - i)
                    dp[i] = max(dp[i], dp[j] + 2);
            }
        }
        return dp.front();
    }
};
