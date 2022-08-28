class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> psum(n + 1);
        vector<double> dp(n + 1);
        for(int i = 1; i <= n; ++i) {
            psum[i] = psum[i - 1] + nums[i - 1];
            dp[i] = (double)psum[i] / i;
        }
        double ans = dp[n];
        while(--k) {
            for(int i = n; i > 0; --i)
                for(int j = 0; j < i; ++j)
                    dp[i] = max(dp[i], dp[j] + (double)(psum[i] - psum[j]) / (i - j));
            ans = max(ans, dp[n]);
        }
        return ans;
    }
};
