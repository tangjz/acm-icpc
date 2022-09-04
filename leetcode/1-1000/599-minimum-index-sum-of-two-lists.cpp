class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        int n = list1.size(), m = list2.size(), ans = INT_MAX;
        map<string, pair<int, int> > mp;
        for(int i = 0; i < n; ++i)
            mp[list1[i]].first = i + 1;
        for(int i = 0; i < m; ++i)
            mp[list2[i]].second = i + 1;
        vector<string> ret;
        for(auto &it: mp) {
            auto jt = it.second;
            if(!jt.first || !jt.second)
                continue;
            int cur = jt.first + jt.second;
            if(cur < ans) {
                ans = cur;
                ret.clear();
            }
            if(cur == ans)
                ret.push_back(it.first);
        }
        return ret;
    }
};
