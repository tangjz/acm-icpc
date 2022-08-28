class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > ret(n, vector<int>(m));
        for(int d = 0; d * 2 < min(n, m); ++d) {
            int xL = d, xR = n - d;
            int yL = d, yR = m - d;
            vector<pair<int, int> > ord;
            for(int i = xL; i < xR; ++i)
                ord.push_back({i, yL});
            for(int i = yL + 1; i < yR; ++i)
                ord.push_back({xR - 1, i});
            for(int i = xR - 2; i >= xL; --i)
                ord.push_back({i, yR - 1});
            for(int i = yR - 2; i > yL; --i)
                ord.push_back({xL, i});
            int sz = ord.size();
            for(int i = 0, j = k % sz; i < sz; ++i, (++j) == sz && (j = 0)) {
                int x1, y1, x2, y2;
                tie(x1, y1) = ord[i];
                tie(x2, y2) = ord[j];
                ret[x2][y2] = grid[x1][y1];
            }
        }
        return ret;
    }
};
