class Solution {
public:
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                bool lft = i == j || i + j == n - 1;
                bool rht = !!grid[i][j];
                if(lft != rht)
                    return 0;
            }
        return 1;
    }
};
