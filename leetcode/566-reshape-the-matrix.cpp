class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int n = mat.size(), m = mat[0].size();
        if(n * m != r * c || n == r)
            return mat;
        vector<vector<int> > ret(r, vector<int>(c));
        for(int i = 0, x = 0, y = 0; i < n; ++i)
            for(int j = 0; j < m; ++j, (++y) == c && (++x, y = 0)) {
                ret[x][y] = mat[i][j];
            }
        return ret;
    }
};
