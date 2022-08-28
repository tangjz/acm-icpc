class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size(), m = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if(m & 3)
            return 0;
        m >>= 2;
        vector<pair<int, int> > dp(1 << n);
        for(int i = 0; i < n; ++i)
            dp[1 << i].second = matchsticks[i];
        for(int i = 1; i < (1 << n); ++i) {
            int lbt = i & -i;
            if(lbt < i)
                dp[i].second = dp[lbt].second + dp[i ^ lbt].second;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1)
                    dp[i].first = max(dp[i].first, dp[i ^ (1 << j)].first);
            dp[i].first += dp[i].second % m == 0;
        }
        return dp.back().first == 4;
    }
};
