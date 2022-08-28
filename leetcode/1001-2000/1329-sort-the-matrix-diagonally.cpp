class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        map<int, multiset<int> > Hash;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                Hash[i - j].insert(mat[i][j]);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                mat[i][j] = *Hash[i - j].begin();
                Hash[i - j].erase(Hash[i - j].begin());
            }
        return mat;
    }
};
