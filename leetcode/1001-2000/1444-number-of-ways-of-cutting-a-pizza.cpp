class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        auto mod_inc = [](int &x, int y) {
            const int mod = (int)1e9 + 7;
            (x += y) >= mod && (x -= mod);
        };
        int r = (int)pizza.size(), c = (int)pizza[0].size();
        vector<vector<int> > s(r + 1, vector<int>(c + 1, 0));
        for(int i = 1; i <= r; ++i)
            for(int j = 1; j <= c; ++j)
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (pizza[i - 1][j - 1] == 'A');
        auto hasApple = [&](int xL, int xR, int yL, int yR) {
            return s[xR][yR] - s[xL - 1][yR] - s[xR][yL - 1] + s[xL - 1][yL - 1] > 0;
        };
        vector<vector<vector<int> > > dp(k, vector<vector<int> >(r, vector<int>(c, 0)));
        for(int i = r - 1; i >= 0; --i)
            for(int j = c - 1; j >= 0; --j) {
                if(hasApple(i + 1, r, j + 1, c))
                    mod_inc(dp[k - 1][i][j], 1);
                for(int p = i + 1; p < r; ++p)
                    if(hasApple(i + 1, p, j + 1, c))
                        for(int q = 1; q < k; ++q)
                            mod_inc(dp[q - 1][i][j], dp[q][p][j]);
                for(int p = j + 1; p < c; ++p)
                    if(hasApple(i + 1, r, j + 1, p))
                        for(int q = 1; q < k; ++q)
                            mod_inc(dp[q - 1][i][j], dp[q][i][p]);
            }
        return dp[0][0][0];
    }
};
