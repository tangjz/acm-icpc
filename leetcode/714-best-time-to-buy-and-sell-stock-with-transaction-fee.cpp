class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int dp[2] = {0, INT_MIN};
        for(int x: prices) {
            int u = max(dp[0], dp[1] > INT_MIN ? dp[1] + x - fee : INT_MIN);
            int v = max(dp[1], dp[0] - x);
            dp[0] = u;
            dp[1] = v;
        }
        return dp[0];
    }
};
