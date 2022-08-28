class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        vector<int> row(n, INT_MAX), col(m, INT_MIN);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int x = mat[i][j];
                row[i] = min(row[i], x);
                col[j] = max(col[j], x);
            }
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int x = mat[i][j];
                if(x == row[i] && x == col[j])
                    ret.push_back(x);
            }
        return ret;
    }
};
