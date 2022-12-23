class Solution {
public:
    int transportationHub(vector<vector<int>>& path) {
        unordered_map<int, pair<int, unordered_set<int> > > e;
        for(auto &it: path) {
            e[it[1]].second.insert(it[0]);
            ++e[it[0]].first;
        }
        for(auto &it: e)
            if(!it.second.first && it.second.second.size() + 1 == e.size())
                return it.first;
        return -1;
    }
};
