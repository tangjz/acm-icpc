class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        vector<vector<int> > ans(r, vector<int>(c));
        vector<unordered_set<int> > sp(r + c + c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int k = i - j + c;
                ans[i][j] = sp[k].size();
                sp[k].insert(mat[i][j]);
            }
        for(int i = 0; i < r + c + c; ++i)
            sp[i].clear();
        for(int i = r - 1; i >= 0; --i)
            for(int j = 0; j < c; ++j) {
                int k = i - j + c;
                ans[i][j] = abs(ans[i][j] - (int)sp[k].size());
                sp[k].insert(mat[i][j]);
            }
        return ans;
    }
};
