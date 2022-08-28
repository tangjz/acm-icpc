class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), ans = 0;
        vector<int> row(r), col(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(!grid[i][j])
                    continue;
                ++ans;
                row[i] = max(row[i], grid[i][j]);
                col[j] = max(col[j], grid[i][j]);
            }
        for(int i = 0; i < r; ++i)
            ans += row[i];
        for(int i = 0; i < c; ++i)
            ans += col[i];
        return ans;
    }
};
