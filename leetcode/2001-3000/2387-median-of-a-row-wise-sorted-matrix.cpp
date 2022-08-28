class Solution {
public:
    int matrixMedian(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<pair<int, int> > seg(m, {0, n});
        vector<int> mid(m);
        int L = grid[0][0], R = grid[0][n - 1];
        for(int i = 1; i < m; ++i) {
            L = min(L, grid[i][0]);
            R = max(R, grid[i][n - 1]);
        }
        int half = (n * m + 1) / 2;
        while(L < R) {
            int M = (L + R) >> 1;
            int ctr = 0;
            for(int i = 0; i < m; ++i) {
                mid[i] = upper_bound(grid[i].begin() + seg[i].first, grid[i].begin() + seg[i].second, M) - grid[i].begin();
                ctr += mid[i];
            }
            if(ctr >= half) {
                R = M;
                for(int i = 0; i < m; ++i)
                    seg[i].second = mid[i];
            } else {
                L = M + 1;
                for(int i = 0; i < m; ++i)
                    seg[i].first = mid[i];
            }
        }
        return L;
    }
};
