class Solution {
public:
    bool removeOnes(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        for(int i = 1; i < r; ++i)
            for(int j = 1; j < c; ++j)
                if(grid[i][j] ^ grid[i][0] ^ grid[0][j] ^ grid[0][0])
                    return 0;
        return 1;
    }
};
