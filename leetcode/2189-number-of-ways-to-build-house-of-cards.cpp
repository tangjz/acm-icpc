class Solution {
public:
    int houseOfCards(int n) {
        int ans = 0, m = n;
        vector<int> dp(n / 3 + 1);
        dp[0] = 1;
        for(int i = 1; (m -= i * 3 - 1) >= 0; ++i) {
            for(int j = i; j <= m / 3; ++j)
                dp[j] += dp[j - i];
            if(m % 3 == 0)
                ans += dp[m / 3];
        }
        return ans;
    }
};
