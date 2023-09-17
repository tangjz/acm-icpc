class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        const int INF = 0x3f3f3f3f;
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for(int x: coins)
            for(int i = x; i <= amount; ++i)
                dp[i] = min(dp[i], dp[i - x] + 1);
        int ans = dp.back();
        return ans < INF ? ans : -1;
    }
};
