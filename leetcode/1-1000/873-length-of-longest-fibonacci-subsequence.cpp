class Solution {
public:
    int lenLongestFibSubseq(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<vector<int> > dp(n, vector<int>(n));
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1, k = 0; j < n; ++j) {
                dp[j][i] = max(dp[j][i], 2);
                for( ; k < i && nums[k] < nums[j] - nums[i]; ++k);
                if(k < i && nums[k] == nums[j] - nums[i])
                    dp[j][i] = max(dp[j][i], dp[i][k] + 1);
                ans = max(ans, dp[j][i]);
            }
        }
        return ans < 3 ? 0 : ans;
    }
};
