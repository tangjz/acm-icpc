class Solution {
public:
    int countEven(int num) {
        int ans = 0;
        vector<int> dp(num + 1);
        for(int i = 1; i <= num; ++i) {
            dp[i] = dp[i / 10] + (i % 10);
            ans += dp[i] % 2 == 0;
        }
        return ans;
    }
};
