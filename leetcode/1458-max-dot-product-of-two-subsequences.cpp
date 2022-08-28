class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        const int maxn = 501;
        int n = (int)nums1.size(), m = (int)nums2.size(), ans = INT_MIN;
        static int dp[maxn][maxn];
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j) {
                if(!i || !j) {
                    dp[i][j] = 0;
                    continue;
                }
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                int tmp = dp[i - 1][j - 1] + nums1[i - 1] * nums2[j - 1];
                dp[i][j] = max(dp[i][j], tmp);
                ans = max(ans, tmp);
            }
        return ans;
    }
};
