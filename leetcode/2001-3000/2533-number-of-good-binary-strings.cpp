class Solution {
public:
    int goodBinaryStrings(int low, int upp, int one, int zero) {
        const int mod = (int)1e9 + 7;
        int ans = 0;
        vector<int> dp(upp + 1);
        dp[0] = 1;
        for(int i = 1; i <= upp; ++i) {
            for(int j: {one, zero})
                if(i >= j)
                    dp[i] = (dp[i] + dp[i - j]) % mod;
            if(i >= low)
                ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};
