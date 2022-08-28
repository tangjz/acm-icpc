class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = 0;
        vector<vector<int> > row(r), col(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(grid[i][j]) {
                    ++n;
                    row[i].push_back(j);
                    col[j].push_back(i);
                }
        int m = ceil(sqrtl(n)), ans = 0;
        vector<pair<int, int> > ctrX(r);
        vector<int> ctrY(c * c);
        for(int i = 0; i < r; ++i) {
            if(row[i].size() < m) {
                int sz = row[i].size();
                for(int j = 0; j < sz; ++j)
                    for(int k = j + 1; k < sz; ++k)
                        ans += ctrY[row[i][j] * c + row[i][k]]++;
                continue;
            }
            ctrX.clear();
            for(int y: row[i])
                for(int x: col[y])
                    if(row[x].size() < m || x < i) {
                        if(ctrX[x].second != i)
                            ctrX[x] = {0, i};
                        ans += ctrX[x].first++;
                    }
        }
        return ans;
    }
};
