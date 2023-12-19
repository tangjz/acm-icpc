class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& mat) {
        const int mod = 12345;
        int r = mat.size(), c = mat[0].size();
        vector<int> row(r), col(c);
        for(int i = 0, prd = 1; i < r; ++i) {
            row[i] = 1;
            for(int j = 0; j < c; ++j) {
                col[j] = mat[i][j] % mod;
                row[i] = row[i] * col[j] % mod;
                mat[i][j] = j ? mat[i][j - 1] * col[j - 1] % mod : prd;
            }
            for(int j = c - 1, tmp = 1; j >= 0; --j) {
                mat[i][j] = mat[i][j] * tmp % mod;
                tmp = tmp * col[j] % mod;
            }
            prd = prd * row[i] % mod;
        }
        for(int i = r - 1, prd = 1; i >= 0; --i) {
            for(int j = 0; j < c; ++j)
                mat[i][j] = mat[i][j] * prd % mod;
            prd = prd * row[i] % mod;
        }
        return mat;
    }
};
