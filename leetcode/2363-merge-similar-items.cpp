class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        map<int, int> ctr;
        for(auto &it: items1)
            ctr[it[0]] += it[1];
        for(auto &it: items2)
            ctr[it[0]] += it[1];
        vector<vector<int> > ret;
        ret.reserve(ctr.size());
        for(auto &it: ctr)
            ret.push_back({it.first, it.second});
        return ret;
    }
};
