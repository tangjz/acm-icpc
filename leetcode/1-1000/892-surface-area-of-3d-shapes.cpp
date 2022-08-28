class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size(), ans = 0;
        auto getH = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < n ? grid[x][y] : 0;
        };
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j) {
                int O = getH(i, j), L = getH(i, j - 1), U = getH(i - 1, j);
                ans += (!!O << 1) + abs(O - L) + abs(O - U);
            }
        return ans;
    }
};
