class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<int> cR(r), cC(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int v = grid[i][j] ? 1 : -1;
                cR[i] += v;
                cC[j] += v;
            }
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                grid[i][j] = cR[i] + cC[j];
        return grid;
    }
};
