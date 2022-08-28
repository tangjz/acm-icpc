class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n + 1);
        dp[0] = 1;
        for(int i = 0; i < n; ++i) {
            if(!dp[i])
                continue;
            if(i + 2 > n)
                continue;
            if(nums[i] == nums[i + 1])
                dp[i + 2] = 1;
            if(i + 3 > n)
                continue;
            if(nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2])
                dp[i + 3] = 1;
            if(nums[i] + 1 == nums[i + 1] && nums[i + 1] + 1 == nums[i + 2])
                dp[i + 3] = 1;
        }
        return dp[n];
    }
};
