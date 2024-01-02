class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        pair<int, int> ans = {};
        for(auto &it: dimensions) {
            int r = it[0], c = it[1];
            ans = max(ans, make_pair(r * r + c * c, r * c));
        }
        return ans.second;
    }
};
