class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        int r = (int)mat.size(), c = (int)mat[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 1; j < c; ++j)
                mat[i][j] += mat[i][j - 1];
        for(int i = 1; i < r; ++i)
            for(int j = 0; j < c; ++j)
                mat[i][j] += mat[i - 1][j];
        vector<vector<int> > ret(r, vector<int>(c));
        auto getSum = [&](int x, int y) {
            return x < 0 || y < 0 ? 0 : mat[min(x, r - 1)][min(y, c - 1)];
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int x0 = i - K, x1 = i + K;
                int y0 = j - K, y1 = j + K;
                ret[i][j] = getSum(x1, y1) - getSum(x0 - 1, y1) - getSum(x1, y0 - 1) + getSum(x0 - 1, y0 - 1);
            }
        return ret;
    }
};
