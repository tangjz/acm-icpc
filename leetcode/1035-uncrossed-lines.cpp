class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> dp(m);
        for(int i = 0; i < n; ++i) {
            int pre = 0;
            for(int j = 0; j < m; ++j) {
                int cur = dp[j];
                if(nums1[i] == nums2[j]) {
                    dp[j] = max(dp[j], pre + 1);
                }
                pre = max(pre, cur);
            }
        }
        int ans = 0;
        for(int i = 0; i < m; ++i)
            ans = max(ans, dp[i]);
        return ans;
    }
};
