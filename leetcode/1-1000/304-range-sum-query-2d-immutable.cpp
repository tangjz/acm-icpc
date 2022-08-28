class NumMatrix {
    vector<vector<int> > mat;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        mat = move(matrix);
        int r = mat.size();
        int c = mat[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 1; j < c; ++j)
                mat[i][j] += mat[i][j - 1];
        for(int i = 1; i < r; ++i)
            for(int j = 0; j < c; ++j)
                mat[i][j] += mat[i - 1][j];
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int row[2] = {row2, row1 - 1};
        int col[2] = {col2, col1 - 1};
        int ret = 0;
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j)
                ret += (i ^ j ? -1 : 1) * (row[i] >= 0 && col[j] >= 0 ? mat[row[i]][col[j]] : 0);
        return ret;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
