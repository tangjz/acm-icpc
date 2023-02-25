class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int> > mat(n + 1, vector<int>(n + 1));
        for(auto &it: queries) {
            ++mat[it[0]][it[1]];
            --mat[it[0]][it[3] + 1];
            --mat[it[2] + 1][it[1]];
            ++mat[it[2] + 1][it[3] + 1];
        }
        mat.pop_back();
        for(int i = 0; i < n; ++i) {
            mat[i].pop_back();
            for(int j = 1; j < n; ++j)
                mat[i][j] += mat[i][j - 1];
        }
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mat[i][j] += mat[i - 1][j];
        return mat;
    }
};
