class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        map<int, int> sp;
        map<int, map<int, int> > dp;
        for(int i = 0; i < n; ++i) {
            int x0 = nums[i];
            map<int, int> upd = sp;
            auto update = [&](int &x, int y) {
                x += y;
            };
            for(auto &it: dp) {
                int x1 = it.first;
                long long x2 = (long long)x1 + x1 - x0;
                if(x2 < INT_MIN || x2 > INT_MAX)
                    continue;
                auto jt = it.second.find((int)x2);
                if(jt != it.second.end()) {
                    update(upd[x1], jt -> second);
                    update(ans, jt -> second);
                }
            }
            ++sp[x0];
            for(auto &it: upd)
                update(dp[x0][it.first], it.second);
        }
        return ans;
    }
};
