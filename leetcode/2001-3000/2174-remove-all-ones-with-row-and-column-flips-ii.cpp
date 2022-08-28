class Solution {
public:
    int removeOnes(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        int n = r * c, mx = 1 << n, sta = 0;
        vector<int> row(r), col(c), dp(mx, INT_MAX);
        dp[0] = 0;
        for(int i = 0, u = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++u) {
                row[i] |= 1 << u;
                col[j] |= 1 << u;
                sta |= grid[i][j] << u;
            }
        for(int i = 1; i < mx; ++i) {
            if((i & sta) != i)
                continue;
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                int ii = i & ~(row[j / c] | col[j % c]);
                dp[i] = min(dp[i], dp[ii] + 1);
            }
        }
        return dp[sta];
    }
};
