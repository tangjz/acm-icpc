class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int ans = 0, n = (int)grid.size(), m = (int)grid[0].size();
        vector<int> row(n), col(m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(grid[i][j]) {
                    ++row[i];
                    ++col[j];
                }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                ans += grid[i][j] && (row[i] > 1 || col[j] > 1);
        return ans;
    }
};
