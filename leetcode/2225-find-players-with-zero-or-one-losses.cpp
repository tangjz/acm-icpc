class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int, pair<int, int> > ctr;
        for(auto &it: matches) {
            ++ctr[it[0]].first;
            ++ctr[it[1]].second;
        }
        vector<vector<int> > ret(2);
        for(auto &it: ctr) {
            int w, l;
            tie(w, l) = it.second;
            if(l < 2)
                ret[l].push_back(it.first);
        }
        for(int i = 0; i < 2; ++i)
            sort(ret[i].begin(), ret[i].end());
        return ret;
    }
};
