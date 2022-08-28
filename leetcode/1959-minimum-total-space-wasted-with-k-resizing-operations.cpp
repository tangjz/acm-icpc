class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int> > dp(n, vector<int>(k + 1, INT_MAX));
        for(int i = 0; i < n; ++i) {
            int upp = nums[i], sum = upp;
            for(int j = i - 1; j >= 0; --j) {
                for(int d = 1; d <= k; ++d)
                    dp[i][d] = min(dp[i][d], dp[j][d - 1] + upp * (i - j) - sum);
                upp = max(upp, nums[j]);
                sum += nums[j];
            }
            for(int d = 0; d <= k; ++d)
                dp[i][d] = min(dp[i][d], upp * (i + 1) - sum);
        }
        return dp.back().back();
    }
};
