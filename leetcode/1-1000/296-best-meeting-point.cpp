class Solution {
    int calc(vector<int> &ctr) {
        int n = ctr.size(), ans = INT_MAX;
        int cL = 0, sL = 0, cR = 0, sR = 0;
        for(int i = 0; i < n; ++i) {
            cR += ctr[i];
            sR += ctr[i] * i;
        }
        for(int i = 0; i < n; ++i) {
            cL += ctr[i];
            sL += ctr[i] * i;
            cR -= ctr[i];
            sR -= ctr[i] * i;
            ans = min(ans, cL * i - sL + sR - cR * i);
        }
        return ans;
    }
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<int> row(r), col(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(grid[i][j]) {
                    ++row[i];
                    ++col[j];
                }
        return calc(row) + calc(col);
    }
};
