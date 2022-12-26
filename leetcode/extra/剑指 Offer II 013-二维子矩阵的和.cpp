class NumMatrix {
    int n, m;
    vector<vector<int> > psum;
    int sumPrefix(int row, int col) {
        return row < 0 || col < 0 ? 0 : psum[row][col];
    }
public:
    NumMatrix(vector<vector<int>>& mat) {
        n = mat.size();
        m = mat[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j)
                mat[i][j] += mat[i][j - 1];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j)
                mat[i][j] += mat[i - 1][j];
        psum = move(mat);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sumPrefix(row2, col2) - sumPrefix(row1 - 1, col2) - sumPrefix(row2, col1 - 1) + sumPrefix(row1 - 1, col1 - 1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
