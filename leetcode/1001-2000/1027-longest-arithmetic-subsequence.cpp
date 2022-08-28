class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        unordered_set<int> sp;
        unordered_map<int, unordered_map<int, int> > dp;
        for(int i = 0; i < n; ++i) {
            int x0 = nums[i];
            unordered_map<int, int> upd;
            auto update = [&](int &x, int y) {
                x < y && (x = y);
            };
            for(int x1: sp)
                update(upd[x1], 2);
            for(auto &it: dp) {
                int x1 = it.first, x2 = x1 + x1 - x0;
                auto jt = it.second.find(x2);
                if(jt != it.second.end())
                    update(upd[x1], (jt -> second) + 1);
            }
            sp.insert(x0);
            for(auto &it: upd) {
                update(dp[x0][it.first], it.second);
                update(ans, it.second);
            }
        }
        return ans;
    }
};
