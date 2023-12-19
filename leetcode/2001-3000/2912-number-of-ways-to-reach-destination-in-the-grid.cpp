class Solution {
public:
    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        typedef long long LL;
        static const int maxn = (int)1e5 + 3, mod = (int)1e9 + 7;
        static int dp[2][maxn], inv[maxn];
        int ways[2] = {n - 1, m - 1};
        for(int i = 0; i < 2; ++i) {
            dp[i][0] = 1;
            dp[i][1] = 0;
            for(int j = 2; j <= k; ++j)
                dp[i][j] = ((LL)(dp[i][j - 2] + dp[i][j - 1]) * ways[i] - dp[i][j - 1]) % mod;
            if(source[i] == dest[i])
                continue;
            for(int j = 0; j <= k; j += 2) {
                (--dp[i][j]) < 0 && (dp[i][j] += mod);
                (++dp[i][j + 1]) >= mod && (dp[i][j + 1] -= mod);
            }
        }
        inv[1] = 1;
        for(int i = 2; i <= k; ++i)
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        int ans = 0, prd = 1;
        for(int i = 0; i <= k; ++i) {
            ans = (ans + (LL)dp[0][i] * dp[1][k - i] % mod * prd) % mod;
            prd = (LL)prd * (k - i) % mod * inv[i + 1] % mod;
        }
        return ans;
    }
};
