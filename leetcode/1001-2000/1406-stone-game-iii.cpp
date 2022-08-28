class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        const int INF = 0x3f3f3f3f;
        int n = (int)stoneValue.size();
        vector<int> dp(n + 1, -INF);
        dp[n] = 0;
        for(int i = n - 1; i >= 0; --i)
            for(int j = 1, sum = 0; j <= 3 && i + j <= n; ++j) {
                sum += stoneValue[i + j - 1];
                dp[i] = max(dp[i], sum - dp[i + j]);
            }
        int res = dp[0];
        return res > 0 ? "Alice" : (res < 0 ? "Bob" : "Tie");
    }
};
