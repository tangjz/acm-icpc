class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& mat) {
        int ans = 0, n = mat.size(), m = mat[0].size();
        unordered_map<string, int> ctr;
        for(int i = 0; i < n; ++i) {
            string rep = "";
            for(int j = 1; j < m; ++j)
                rep.push_back("01"[mat[i][0] != mat[i][j]]);
            ++ctr[rep];
        }
        for(auto &it: ctr)
            ans = max(ans, it.second);
        return ans;
    }
};
