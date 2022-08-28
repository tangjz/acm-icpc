class Solution {
public:
    void setZeroes(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        bool sp = false;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(mat[i][j])
                    continue;
                if(!j) {
                    sp = true;
                } else {
                    mat[0][j] = 0;
                }
                mat[i][0] = 0;
            }
        for(int i = n - 1; i >= 0; --i)
            for(int j = m - 1; j >= 0; --j) {
                if(!mat[i][j])
                    continue;
                if(!mat[i][0]) {
                    mat[i][j] = 0;
                    continue;
                }
                if((!j && sp) || (j && !mat[0][j])) {
                    mat[i][j] = 0;
                    continue;
                }
            }
    }
};
