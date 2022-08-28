class Solution {
public:
    int kthLargestValue(vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 1; j < m; ++j)
                mat[i][j] ^= mat[i][j - 1];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j)
                mat[i][j] ^= mat[i - 1][j];
        vector<int> seq;
        seq.reserve(n * m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                seq.push_back(mat[i][j]);
        nth_element(seq.begin(), seq.begin() + (n * m - k), seq.end());
        return seq[n * m - k];
    }
};
