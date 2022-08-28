class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        const int INF = 0x3f3f3f3f;
        int n = nums.size(), m = n / k;
        sort(nums.begin(), nums.end());
        vector<vector<int> > dp(1 << n, vector<int>(n, INF));
        for(int i = 0; i < n; ++i) {
            dp[1 << i][i] = 0;
        }
        for(int s = 1; s < (1 << n) - 1; ++s) {
            int c = __builtin_popcount(s);
            if(c % m == 0) {
                int low = *min_element(dp[s].begin(), dp[s].end());
                for(int i = 0, t = 1; i < n; ++i, t <<= 1) {
                    if(s & t)
                        continue;
                    dp[s | t][i] = min(dp[s | t][i], low);
                }
            } else {
                int low = INF, j = 0, u = 1;
                for(int i = 0, t = 1; i < n; ++i, t <<= 1) {
                    if(s & t)
                        continue;
                    for( ; nums[j] < nums[i]; ++j, u <<= 1)
                        if(s & u) {
                            // printf("gather %d %d: %d - %d\n", s, j, dp[s][j], nums[j]);
                            low = min(low, dp[s][j] - nums[j]);
                        }
                    // printf("upd %d %d: %d + %d\n", s | t, i, low, nums[i]);
                    dp[s | t][i] = min(dp[s | t][i], low + nums[i]);
                }
            }
            // for(int i = 0; i < n; ++i)
            //     if(dp[s][i] < INF)
            //         printf("%d %d: %d\n", s, i, dp[s][i]);
        }
        // for(int i = 0; i < n; ++i)
        //     if(dp.back()[i] < INF)
        //         printf("%d %d: %d\n", (1 << n) - 1, i, dp.back()[i]);
        int ans = *min_element(dp.back().begin(), dp.back().end());
        return ans < INF ? ans : -1;
    }
};
