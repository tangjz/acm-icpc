class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<vector<int> > pR(n);
        for(int i = 0; i <= (n - 1) * 2; ++i) {
            int L = i / 2, R = i - L;
            for( ; L >= 0 && R < n && s[L] == s[R]; --L, ++R)
                if(R - L + 1 >= k)
                    pR[L].push_back(R + 1);
        }
        vector<int> dp(n + 1);
        for(int i = 0; i < n; ++i) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            for(int j: pR[i])
                dp[j] = max(dp[j], dp[i] + 1);
        }
        return dp[n];
    }
};
