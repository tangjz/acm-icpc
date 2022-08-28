class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        int n = username.size();
        map<vector<string>, set<string> > ctr;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if(timestamp[i] >= timestamp[j] || username[i] != username[j])
                    continue;
                for(int k = 0; k < n; ++k) {
                    if(timestamp[j] >= timestamp[k] || username[j] != username[k])
                        continue;
                    ctr[{website[i], website[j], website[k]}].insert(username[i]);
                }
            }
        pair<int, vector<string> > ret;
        for(auto &it: ctr)
            ret = min(ret, make_pair(-(int)it.second.size(), it.first));
        return ret.second;
    }
};
