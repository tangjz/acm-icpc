class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        vector<int> row(n, -1), col(m, -1);
        auto upd = [](int &x, int y) {
            if(x == -1) {
                x = y;
            } else {
                x = -2;
            }
        };
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(mat[i][j] == 1) {
                    upd(row[i], j);
                    upd(col[j], i);
                }
        int ret = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(row[i] == j && col[j] == i)
                    ++ret;
        return ret;
    }
};
