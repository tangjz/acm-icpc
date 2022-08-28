class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size();
        for(int i = 0; i < n - 2; ++i) {
            for(int j = 0; j < n - 2; ++j) {
                for(int x = 0; x < 3; ++x)
                    for(int y = 0; y < 3; ++y) {
                        int val = grid[i + x][j + y];
                        grid[i][j] = max(grid[i][j], val);
                    }
            }
            grid[i].resize(n - 2);
        }
        grid.resize(n - 2);
        return grid;
    }
};
