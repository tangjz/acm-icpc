class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<pair<int, int> > dp(n);
        for(int i = 0; i < n; ++i) {
            dp[i] = {1, 1};
            for(int j = 0; j < i; ++j)
                if(nums[j] < nums[i]) {
                    dp[i].second = max(dp[i].second, dp[j].first + 1);
                } else if(nums[j] > nums[i]) {
                    dp[i].first = max(dp[i].first, dp[j].second + 1);
                }
            ans = max(ans, max(dp[i].first, dp[i].second));
        }
        return ans;
    }
};
