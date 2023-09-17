class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size(), n = r * c;
        vector<pair<int, int> > pos(n + 1);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                pos[mat[i][j]] = {i, j};
        vector<int> row(r), col(c);
        for(int i = 0; i < n; ++i) {
            auto &[x, y] = pos[arr[i]];
            if((++row[x]) == c || (++col[y]) == r)
                return i;
        }
        return -1;
    }
};
