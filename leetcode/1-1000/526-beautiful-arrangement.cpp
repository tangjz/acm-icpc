class Solution {
public:
    int countArrangement(int n) {
        int all = (1 << n) - 1;
        vector<pair<int, int> > dp(all + 1);
        dp[0] = {1, 0};
        for(int i = 1; i <= all; ++i) {
            dp[i].second = dp[i >> 1].second + (i & 1);
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1 && (dp[i].second % (j + 1) == 0 || (j + 1) % dp[i].second == 0))
                    dp[i].first += dp[i ^ (1 << j)].first;
        }
        return dp.back().first;
    }
};
