class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int r = mat.size(), c = mat[0].size();
        for(int i = 0; i < r; ++i)
            for(int u = 0, v = k % c; u < c; ++u, (++v) == c && (v = 0))
                if(mat[i][u] != mat[i][v])
                    return 0;
        return 1;
    }
};
