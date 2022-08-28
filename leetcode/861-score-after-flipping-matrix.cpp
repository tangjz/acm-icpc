class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        int ans = r << (c - 1);
        for(int i = 1; i < c; ++i) {
            int ctr = 0;
            for(int j = 0; j < r; ++j)
                ctr += grid[j][i] != grid[j][0];
            ctr = max(ctr, r - ctr);
            ans += ctr << (c - 1 - i);
        }
        return ans;
    }
};
