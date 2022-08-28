class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0;
        for(int x: nums)
            sum += x;
        if(sum % k > 0)
            return 0;
        sum /= k;
        vector<int> dp(1 << n), sub(1 << n);
        for(int i = 0; i < n; ++i)
            sub[1 << i] = nums[i];
        for(int i = 1; i < (1 << n); ++i) {
            int lbt = i & -i;
            if(lbt < i)
                sub[i] = sub[i ^ lbt] + sub[lbt];
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1)
                    dp[i] = max(dp[i], dp[i ^ (1 << j)]);
            dp[i] += sub[i] % sum == 0;
        }
        return dp.back() == k;
    }
};
