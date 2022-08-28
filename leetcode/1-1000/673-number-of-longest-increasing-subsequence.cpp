class Solution {
    void combine(pair<int, int> &dst, pair<int, int> const &src) {
        if(dst.first < src.first) {
            dst = {src.first, 0};
        }
        if(dst.first == src.first) {
            dst.second += src.second;
        }
    }
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        pair<int, int> ans = {0, 0};
        vector<pair<int, int> > dp(n);
        for(int i = 0; i < n; ++i) {
            combine(dp[i], {1, 1});
            for(int j = 0; j < i; ++j)
                if(nums[j] < nums[i])
                    combine(dp[i], {dp[j].first + 1, dp[j].second});
            combine(ans, dp[i]);
        }
        return ans.second;
    }
};
