class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > dp(n, vector<int>(m));
        if(!grid[0][0])
            dp[0][0] += 1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(grid[i][j])
                    continue;
                if(i)
                    dp[i][j] += dp[i - 1][j];
                if(j)
                    dp[i][j] += dp[i][j - 1];
            }
        return dp.back().back();
    }
};
