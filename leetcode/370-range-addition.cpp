class Solution {
public:
    vector<int> getModifiedArray(int n, vector<vector<int>>& inc) {
        vector<int> ret(n + 1);
        for(auto &it: inc) {
            ret[it[0]] += it[2];
            ret[it[1] + 1] -= it[2];
        }
        for(int i = 0; i < n; ++i)
            ret[i + 1] += ret[i];
        ret.pop_back();
        return ret;
    }
};
