class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        int r = mat.size(), c = mat[0].size();
        pair<int, int> ans = {-1, -1};
        for(int i = 0; i < r; ++i) {
            int ctr = 0;
            for(int j = 0; j < c; ++j)
                ctr += mat[i][j];
            ans = max(ans, make_pair(ctr, -i));
        }
        return {-ans.second, ans.first};
    }
};
