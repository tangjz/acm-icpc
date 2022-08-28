class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        const int mod = (int)1e9 + 7, maxd = 26;
        auto mod_inc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        int m = (int)evil.size();
        vector<int> fail(m + 1, 0);
        for(int i = 1, j = 0; i < m; ++i) {
            for( ; j && evil[i] != evil[j]; j = fail[j]);
            fail[i + 1] = evil[i] == evil[j] ? (++j) : 0;
        }
        vector<vector<vector<int> > > dp(n + 1, vector<vector<int> >(4, vector<int>(m, 0)));
        dp[0][0][0] = 1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < 4; ++j)
                for(int k = 0; k < m; ++k) {
                    if(!dp[i][j][k])
                        continue;
                    int L = (j & 1) ? 0 : (s1[i] - 'a');
                    int R = (j & 2) ? maxd - 1 : (s2[i] - 'a');
                    for(int x = L; x <= R; ++x) {
                        int jj = j | (x > L) | ((x < R) << 1);
                        int kk = k;
                        for( ; kk && evil[kk] - 'a' != x; kk = fail[kk]);
                        kk += evil[kk] - 'a' == x;
                        if(kk < m)
                            mod_inc(dp[i + 1][jj][kk], dp[i][j][k]);
                    }
                }
        int ans = 0;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < m; ++j)
                mod_inc(ans, dp[n][i][j]);
        return ans;
    }
};
