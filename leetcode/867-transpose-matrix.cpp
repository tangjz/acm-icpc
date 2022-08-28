class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        vector<vector<int> > ret(c, vector<int>(r));
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                ret[j][i] = mat[i][j];
        return ret;
    }
};
