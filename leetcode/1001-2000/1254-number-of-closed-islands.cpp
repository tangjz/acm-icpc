class Solution {
    int dfs(int x, int y, int n, int m, vector<vector<int> > &grid) {
        if(x < 0 || x >= n || y < 0 || y >= m || grid[x][y])
            return 1;
        grid[x][y] = -1;
        int ret = x > 0 && x < n - 1 && y > 0 && y < m - 1;
        ret &= dfs(x - 1, y, n, m, grid);
        ret &= dfs(x, y - 1, n, m, grid);
        ret &= dfs(x, y + 1, n, m, grid);
        ret &= dfs(x + 1, y, n, m, grid);
        return ret;
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        int n = (int)grid.size(), m = (int)grid[0].size(), ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(grid[i][j])
                    continue;
                ans += dfs(i, j, n, m, grid);
            }
        return ans;
    }
};
