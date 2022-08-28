class Solution {
public:
    int keyboard(int k, int n) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        vector<int> inv(k + 1), dp(n + 1);
        inv[1] = 1;
        for(int i = 2; i <= k; ++i)
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        dp[0] = 1;
        for(int i = 0; i < 26; ++i)
            for(int j = n; j >= 0; --j)
                for(int x = 1, prd = 1; x <= k && x <= j; ++x) {
                    prd = (LL)prd * inv[x] % mod;
                    dp[j] = (dp[j] + (LL)prd * dp[j - x]) % mod;
                }
        int ans = dp[n];
        for(int i = 1; i <= n; ++i)
            ans = (LL)ans * i % mod;
        return ans;
    }
};
