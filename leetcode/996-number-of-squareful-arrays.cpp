class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size(), m = 1 << n;
        vector<vector<int> > dp(m, vector<int>(n)), good(n, vector<int>(n));
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i) {
            if(!i || nums[i - 1] != nums[i])
                dp[1 << i][i] = 1;
            for(int j = 0; j < n; ++j) {
                if(j <= i) {
                    good[i][j] = good[j][i];
                    continue;
                }
                long long s = nums[i] + nums[j], x = sqrtl(s);
                for( ; x * x <= s; ++x);
                for( ; x * x > s; --x);
                good[i][j] = x * x == s;
            }
        }
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                if(j > 0 && nums[j - 1] == nums[j] && !((i >> (j - 1)) & 1))
                    continue;
                for(int k = 0; k < n; ++k) {
                    if(j == k || !((i >> k) & 1) || !good[j][k])
                        continue;
                    // printf("%d %d <- %d %d\n", i, j, i ^ (1 << j), k);
                    dp[i][j] += dp[i ^ (1 << j)][k];
                }
            } puts("");
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += dp[m - 1][i];
        return ans;
    }
};
