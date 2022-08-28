class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        const unsigned int maxv = INT_MAX;
        vector<unsigned> dp(target + 1);
        dp[0] = 1;
        for(int i = 1; i <= target; ++i)
            for(int x: nums)
                i >= x && (dp[i] += dp[i - x]) >= maxv && (dp[i] = maxv);
        return dp.back();
    }
};
