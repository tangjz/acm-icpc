class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int> > e;
        for(auto &it: adjacentPairs) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        int cur = INT_MAX, pre = INT_MAX;
        for(auto &it: e)
            if(it.second.size() == 1)
                cur = it.first;
        vector<int> ret;
        while(true) {
            ret.push_back(cur);
            int nxt = INT_MAX;
            for(int tmp: e[cur])
                if(tmp != pre)
                    nxt = tmp;
            if(nxt == INT_MAX)
                break;
            pre = cur;
            cur = nxt;
        }
        return ret;
    }
};
