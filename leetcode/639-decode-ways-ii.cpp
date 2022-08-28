class Solution {
public:
    int numDecodings(string s) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = s.size();
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(int i = 0; i < n; ++i) {
            int xL, xR;
            if(s[i] == '*') {
                xL = 1;
                xR = 9;
            } else {
                xL = xR = s[i] - '0';
            }
            for(int x = max(xL, 1); x <= xR; ++x) {
                (dp[i + 1] += dp[i]) >= mod && (dp[i + 1] -= mod);
                if(i + 1 == n)
                    continue;
                int yL, yR;
                if(s[i + 1] == '*') {
                    yL = 1;
                    yR = 9;
                } else {
                    yL = yR = s[i + 1] - '0';
                }
                for(int y = yL; y <= yR && x * 10 + y <= 26; ++y)
                    (dp[i + 2] += dp[i]) >= mod && (dp[i + 2] -= mod);
            }
        }
        return dp[n];
    }
};
