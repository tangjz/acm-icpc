class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int best = 0;
                if(i > 0)
                    best = grid[i - 1][j];
                if(j > 0)
                    best = max(best, grid[i][j - 1]);
                grid[i][j] += best;
            }
        return grid[r - 1][c - 1];
    }
};
