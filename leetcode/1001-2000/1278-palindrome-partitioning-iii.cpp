class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = (int)s.size();
        vector<vector<int> > cost(n, vector<int>(n));
        for(int i = 0; i < n; ++i)
            cost[i][i] = 0;
        for(int i = 1; i < n; ++i)
            cost[i - 1][i] = s[i - 1] != s[i];
        for(int len = 3; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R)
                cost[L][R] = (s[L] != s[R]) + cost[L + 1][R - 1];
        vector<vector<int> > dp(n + 1, vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        for(int L = 0; L < n; ++L)
            for(int R = L; R < n; ++R)
                for(int i = 0; i < k; ++i)
                    if(dp[L][i] < INT_MAX)
                        dp[R + 1][i + 1] = min(dp[R + 1][i + 1], dp[L][i] + cost[L][R]);
        return dp[n][k];
    }
};
