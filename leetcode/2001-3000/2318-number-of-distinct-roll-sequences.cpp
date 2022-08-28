class Solution {
public:
    int distinctSequences(int n) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7, maxn = (int)1e4 + 1;
        static int com[7][7] = {}, dp[maxn][7][7] = {}, mx = 0, f[maxn] = {};
        if(n == 1)
            return 6;
        if(!com[1][1]) {
            for(int i = 0; i < 7; ++i)
                for(int j = 0; j < 7; ++j) {
                    com[i][j] = i > j ? com[j][i] : (i ? com[i][j - i] : j);
                    if(i > 0 && j > 0 && com[i][j] == 1 && i != j) {
                        dp[2][i][j] = 1;
                        ++f[2];
                    }
                }
            mx = 2;
        }
        for( ; mx < n; ++mx) {
            for(int i = 1; i < 7; ++i)
                for(int j = 1; j < 7; ++j) {
                    if(!dp[mx][i][j])
                        continue;
                    for(int k = 1; k < 7; ++k) {
                        if(com[j][k] != 1 || k == j || k == i)
                            continue;
                        (dp[mx + 1][j][k] += dp[mx][i][j]) >= mod && (dp[mx + 1][j][k] -= mod);
                        (f[mx + 1] += dp[mx][i][j]) >= mod && (f[mx + 1] -= mod);
                    }
                }
        }
        return f[n];
    }
};
