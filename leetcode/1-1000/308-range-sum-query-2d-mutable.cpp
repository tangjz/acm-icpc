class NumMatrix {
    int n, m;
    vector<vector<int> > mat;
    vector<vector<long long> > bits;

    long long query(int row, int col) {
        if(row < 0 || col < 0)
            return 0;
        long long ret = 0;
        for(int x = row + 1; x > 0; x -= x & -x)
            for(int y = col + 1; y > 0; y -= y & -y)
                ret += bits[x - 1][y - 1];
        return ret;
    }
public:
    NumMatrix(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        vector<vector<long long> >(n, vector<long long>(m)).swap(bits);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                for(int x = i + 1; x <= n; x += x & -x)
                    for(int y = j + 1; y <= m; y += y & -y)
                        bits[x - 1][y - 1] += matrix[i][j];
        mat = move(matrix);
    }

    void update(int row, int col, int val) {
        int dt = val - mat[row][col];
        for(int x = row + 1; x <= n; x += x & -x)
            for(int y = col + 1; y <= m; y += y & -y)
                bits[x - 1][y - 1] += dt;
        mat[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return query(row2, col2) - query(row1 - 1, col2) - query(row2, col1 - 1) + query(row1 - 1, col1 - 1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
