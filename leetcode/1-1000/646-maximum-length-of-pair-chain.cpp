class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        map<int, int> dp;
        for(auto &it: pairs) {
            int L = it[0], R = it[1];
            auto jt = dp.find(R);
            if(jt == dp.end()) {
                dp.insert({R, L});
            } else {
                jt -> second = max(jt -> second, L);
            }
        }
        int ans = 0;
        for(auto &it: dp) {
            int R = it.first, L = it.second;
            it.second = 1;
            auto jt = dp.lower_bound(L);
            if(jt != dp.begin())
                it.second = max(it.second, (--jt) -> second + 1);
            ans = it.second = max(ans, it.second);
        }
        return ans;
    }
};
