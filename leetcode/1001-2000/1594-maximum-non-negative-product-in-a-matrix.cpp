class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        typedef long long LL;
        int n = grid.size(), m = grid[0].size();
        vector<vector<pair<LL, LL> > > dp(n, vector<pair<LL, LL> >(m, {LLONG_MAX, LLONG_MIN}));
        dp[0][0] = {grid[0][0], grid[0][0]};
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(i > 0) {
                    LL u = dp[i - 1][j].first * grid[i][j];
                    LL v = dp[i - 1][j].second * grid[i][j];
                    if(u > v)
                        swap(u, v);
                    dp[i][j] = {min(dp[i][j].first, u), max(dp[i][j].second, v)};
                }
                if(j > 0) {
                    LL u = dp[i][j - 1].first * grid[i][j];
                    LL v = dp[i][j - 1].second * grid[i][j];
                    if(u > v)
                        swap(u, v);
                    dp[i][j] = {min(dp[i][j].first, u), max(dp[i][j].second, v)};
                }
            }
        return max(dp.back().back().second, -1LL) % ((int)1e9 + 7);
    }
};
