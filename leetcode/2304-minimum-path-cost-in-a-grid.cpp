class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int r = grid.size(), c = grid[0].size();
        vector<int> f = grid[0], g(c);
        for(int i = 0; i + 1 < r; ++i) {
            g.assign(c, INT_MAX);
            for(int j = 0; j < c; ++j) {
                int v = grid[i][j];
                for(int k = 0; k < c; ++k) {
                    g[k] = min(g[k], f[j] + moveCost[v][k] + grid[i + 1][k]);
                }
            }
            f.swap(g);
        }
        return *min_element(f.begin(), f.end());
    }
};
