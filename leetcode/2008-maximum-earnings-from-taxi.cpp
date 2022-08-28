class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& req) {
        typedef long long LL;
        int m = req.size();
        vector<LL> dp(n + 1);
        sort(req.begin(), req.end(), [&](auto const &lft, auto const &rht) {
            return lft[1] < rht[1];
        });
        for(int i = 1, j = 0; i <= n; ++i) {
            dp[i] = dp[i - 1];
            for( ; j < m && req[j][1] == i; ++j) {
                dp[i] = max(dp[i], dp[req[j][0]] + req[j][1] - req[j][0] + req[j][2]);
            }
        }
        return dp[n];
    }
};
