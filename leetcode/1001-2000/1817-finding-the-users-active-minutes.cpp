class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, unordered_set<int> > ctr;
        for(auto &it: logs)
            ctr[it[0]].insert(it[1]);
        vector<int> ret(k);
        for(auto &it: ctr) {
            int sz = it.second.size();
            if(sz > 0 && sz <= k)
                ++ret[sz - 1];
        }
        return ret;
    }
};
