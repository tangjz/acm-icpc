class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        const int INF = 0x3f3f3f3f;
        int n = nums.size();
        if(n <= 2) {
            return n == 2 && nums[0] == nums[1];
        }
        vector<int> dp(n, INF);
        dp[0] = 0;
        dp[1] = max(nums[0] - nums[1] + 1, 0);
        for(int i = 2; i < n; ++i) {
            dp[i] = dp[i - 2] + max(nums[i - 1] - min(nums[i - 2], nums[i]) + 1, 0);
        }
        int ans = dp[n - 1];
        ans = min(ans, dp[n - 2] + max(nums[n - 1] - nums[n - 2] + 1, 0));
        return ans;
    }
};
