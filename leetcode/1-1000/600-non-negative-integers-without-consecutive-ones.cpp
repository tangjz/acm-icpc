class Solution {
public:
    int findIntegers(int n) {
        ++n;
        int mx = 0;
        for( ; (1 << mx) <= n; ++mx);
        vector<int> dp = {1, 2};
        for(int i = 2; i < mx; ++i)
            dp.push_back(dp[i - 1] + dp[i - 2]);
        int ans = 0;
        for(int i = mx - 1, las = 0, cur = 0; i >= 0; --i) {
            cur = (n >> i) & 1;
            if(cur)
                ans += dp[i];
            if(las && cur)
                break;
            las = cur;
        }
        return ans;
    }
};
