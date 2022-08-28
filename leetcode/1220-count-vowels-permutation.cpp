class Solution {
public:
    int countVowelPermutation(int n) {
        const int maxd = 5, mod = (int)1e9 + 7;
        vector<vector<int> > dp(n + 1, vector<int>(maxd));
        for(int i = 0; i < maxd; ++i) {
            dp[1][i] = 1;
        }
        auto modInc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        auto modDec = [&](int &x, int y) {
            (x -= y) < 0 && (x += mod);
        };
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < maxd; ++j) {
                if(j & 1) {
                    modInc(dp[i + 1][j - 1], dp[i][j]);
                    modInc(dp[i + 1][j + 1], dp[i][j]);
                } else if(j == 2) {
                    for(int k = 0; k < maxd; ++k)
                        if(k != 2)
                            modInc(dp[i + 1][k], dp[i][j]);
                } else {
                    modInc(dp[i + 1][(j + 1) % maxd], dp[i][j]);
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < maxd; ++i)
            modInc(ans, dp[n][i]);
        return ans;
    }
};
