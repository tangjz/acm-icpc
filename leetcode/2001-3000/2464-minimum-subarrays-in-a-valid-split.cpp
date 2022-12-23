class Solution {
public:
    int validSubarraySplit(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, -1);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            if(dp[i] == -1)
                continue;
            for(int j = i + 1; j <= n; ++j)
                if(gcd(nums[i], nums[j - 1]) > 1)
                    dp[j] = min(dp[j] == -1 ? INT_MAX : dp[j], dp[i] + 1);
        }
        return dp[n];
    }
};
