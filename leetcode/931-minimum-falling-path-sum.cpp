class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        for(int i = 1; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int best = mat[i - 1][j];
                if(j)
                    best = min(best, mat[i - 1][j - 1]);
                if(j + 1 < c)
                    best = min(best, mat[i - 1][j + 1]);
                mat[i][j] += best;
            }
        return *min_element(mat[r - 1].begin(), mat[r - 1].end());
    }
};
