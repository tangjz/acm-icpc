class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp[3] = {}, las = ~0U >> 1;
        for(int x : prices) {
            int tmp = dp[2];
            dp[2] = dp[1] + (x - las);
            dp[1] = max(dp[0], dp[2]);
            dp[0] = max(dp[0], tmp);
            las = x;
        }
        return max(dp[0], dp[2]);
    }
};
