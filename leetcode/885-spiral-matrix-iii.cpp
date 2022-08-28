class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        vector<vector<int> > ret;
        ret.reserve(rows * cols);
        int d = 0, x = rStart, y = cStart;
        ret.push_back({x, y});
        for(int i = 1; i <= rows * 2 || i <= cols * 2; ++i)
            for(int j = 0; j < 2; ++j, d = (d + 1) & 3)
                for(int k = 0; k < i; ++k) {
                    x += dx[d];
                    y += dy[d];
                    if(x >= 0 && x < rows && y >= 0 && y < cols)
                        ret.push_back({x, y});
                }
        return ret;
    }
};
