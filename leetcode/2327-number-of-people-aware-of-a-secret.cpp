class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int mod = (int)1e9 + 7;
        int ans = 0;
        vector<int> dp(n);
        dp[0] = 1;
        for(int i = 0; i < n; ++i) {
            for(int j = i + delay; j < i + forget && j < n; ++j)
                dp[j] = (dp[j] + dp[i]) % mod;
            if(i + forget >= n)
                ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};
