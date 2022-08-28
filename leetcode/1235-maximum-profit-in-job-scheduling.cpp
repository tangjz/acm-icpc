class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = (int)profit.size();
        vector<int> ord(n), dp(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return startTime[u] < startTime[v];
        });
        for(int i = n - 1; i >= 0; --i) {
            dp[i] = profit[ord[i]];
            int j = lower_bound(ord.begin(), ord.end(), endTime[ord[i]], [&](int const &u, int const &tim) {
                return startTime[u] < tim;
            }) - ord.begin();
            if(j < n)
                dp[i] += dp[j];
            if(i + 1 < n)
                dp[i] = max(dp[i], dp[i + 1]);
        }
        return dp[0];
    }
};
