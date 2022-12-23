class Solution {
public:
    int deleteString(string s) {
        int n = s.size();
        vector<vector<int> > lcp(n, vector<int>(n));
        for(int i = n - 1; i >= 0; --i)
            for(int j = n - 1; j > i; --j)
                lcp[i][j] = s[i] == s[j] ? (j + 1 < n ? lcp[i + 1][j + 1] : 0) + 1 : 0;
        vector<int> dp(n + 1, INT_MIN);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            // printf("dp %d: %d\n", i, dp[i]);
            if(dp[i] == INT_MIN)
                continue;
            dp[n] = max(dp[n], dp[i] + 1);
            for(int j = i + 1, k = i + 2; k <= n; ++j, k += 2)
                if(j + lcp[i][j] >= k)
                    dp[j] = max(dp[j], dp[i] + 1);
        }
        return dp[n];
    }
};
