class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int ans = 0;
        vector<vector<int> > lft, rht;
        for(auto &it: events) {
            ans = max(ans, it[2]);
            lft.push_back({it[0], it[2]});
            rht.push_back({it[1], it[2]});
        }
        sort(lft.begin(), lft.end());
        sort(rht.begin(), rht.end());
        int upp = 0;
        auto jt = rht.begin();
        for(auto &it: lft) {
            while(jt != rht.end() && (*jt)[0] < it[0]) {
                upp = max(upp, (*jt)[1]);
                ++jt;
            }
            ans = max(ans, it[1] + upp);
        }
        return ans;
    }
};
