class Solution {
public:
    int minimumBeautifulSubstrings(string s) {
        int n = s.size();
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            if(dp[i] > n || s[i] == '0')
                continue;
            int u = 0, v = 1;
            for(int j = i; j < n; ++j) {
                u = u << 1 | (s[j] - '0');
                for( ; v < u; v *= 5);
                if(u == v)
                    dp[j + 1] = min(dp[j + 1], dp[i] + 1);
            }
        }
        return dp[n] <= n ? dp[n] : -1;
    }
};
