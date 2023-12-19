class Solution {
public:
    int maxSubarrays(vector<int>& nums) {
        int n = nums.size(), s = nums[0];
        for(int x: nums)
            s &= x;
        if(s > 0)
            return 1;
        vector<int> dp(n + 1);
        vector<pair<int, int> > stk;
        for(int i = 0; i < n; ++i) {
            int sz = 0, v = nums[i];
            for(pair<int, int> &cur: stk) {
                cur.first &= v;
                if(!sz || cur.first != stk[sz - 1].first) {
                    stk[sz++] = cur;
                } else {
                    stk[sz - 1].second = cur.second;
                }
            }
            stk.resize(sz);
            if(!sz || v != stk[sz - 1].first) {
                stk.push_back({v, i});
            } else {
                stk[sz - 1].second = i;
            }
            dp[i + 1] = max(dp[i + 1], dp[i]);
            if(!stk[0].first)
                dp[i + 1] = max(dp[i + 1], dp[stk[0].second] + 1);
        }
        return dp[n];
    }
};
