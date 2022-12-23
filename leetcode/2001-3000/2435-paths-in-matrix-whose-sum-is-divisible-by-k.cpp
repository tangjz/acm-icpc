class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        const int mod = (int)1e9 + 7;
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<vector<int> > dp(n, vector<int>(k));
        dp[0][grid[0][0] % k] = 1;
        for(int i = 1; i < n; ++i) {
            int x = i / c, y = i % c, z = grid[x][y] % k;
            if(x > 0) {
                for(int u = 0, v = z; u < k; ++u, (++v) == k && (v = 0))
                    (dp[i][v] += dp[i - c][u]) >= mod && (dp[i][v] -= mod);
            }
            if(y > 0) {
                for(int u = 0, v = z; u < k; ++u, (++v) == k && (v = 0))
                    (dp[i][v] += dp[i - 1][u]) >= mod && (dp[i][v] -= mod);
            }
        }
        return dp[n - 1][0];
    }
};
