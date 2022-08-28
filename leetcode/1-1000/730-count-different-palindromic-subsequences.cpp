class Solution {
public:
    int countPalindromicSubsequences(string s) {
        static const int maxn = (int)1e3 + 1, mod = (int)1e9 + 7;
        static int dp[5][maxn][maxn];
        int n = s.size();
        auto modInc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        for(int i = 0; i < n; ++i) {
            dp[4][i][i] = 0;
            if(i + 1 < n)
                dp[4][i][i + 1] = 0;
            for(int j = 0; j < 4; ++j) {
                dp[j][i][i] = s[i] == 'a' + j;
                modInc(dp[4][i][i], dp[j][i][i]);
                if(i + 1 < n) {
                    dp[j][i][i + 1] = (s[i] == 'a' + j || s[i + 1] == 'a' + j);
                    if(dp[j][i][i + 1])
                        modInc(dp[j][i][i + 1], s[i] == s[i + 1]);
                    modInc(dp[4][i][i + 1], dp[j][i][i + 1]);
                }
            }
        }
        for(int len = 3; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                dp[4][L][R] = 0;
                for(int j = 0; j < 4; ++j) {
                    if(s[L] != 'a' + j) {
                        dp[j][L][R] = dp[j][L + 1][R];
                    } else if(s[R] != 'a' + j) {
                        dp[j][L][R] = dp[j][L][R - 1];
                    } else {
                        dp[j][L][R] = 2;
                        modInc(dp[j][L][R], dp[4][L + 1][R - 1]);
                    }
                    modInc(dp[4][L][R], dp[j][L][R]);
                }
            }
        return dp[4][0][n - 1];
    }
};
