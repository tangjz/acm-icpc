class Solution {
public:
    int deleteGreatestValue(vector<vector<int>>& A) {
        int r = A.size(), c = A[0].size();
        vector<int> ans(c);
        for(int i = 0; i < r; ++i) {
            sort(A[i].begin(), A[i].end());
            for(int j = 0; j < c; ++j)
                ans[j] = max(ans[j], A[i][j]);
        }
        return accumulate(ans.begin(), ans.end(), 0);
    }
};
