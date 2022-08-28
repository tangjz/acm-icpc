class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& mat) {
        int r = mat.size(), c = mat[0].size(), ans = 0;
        vector<int> row(r), col(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(mat[i][j] == 'B') {
                    ++row[i];
                    ++col[j];
                }
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(mat[i][j] == 'B')
                    ans += row[i] == 1 && col[j] == 1;
        return ans;
    }
};
