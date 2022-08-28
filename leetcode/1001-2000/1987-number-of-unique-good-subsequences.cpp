class Solution {
    static const int mod = (int)1e9 + 7;
    int solve(string str) {
        int dp[3] = {};
        dp[2] = 1;
        for(char ch: str) {
            int o = ch - '0';
            int old = dp[2];
            dp[2] = (dp[2] + dp[2] - dp[o]) % mod;
            dp[2] < 0 && (dp[2] += mod);
            dp[o] = old;
            // printf("%d: %d %d %d\n", o, dp[0], dp[1], dp[2]);
        }
        int ans = (dp[2] + mod - 1) % mod; // exclude ""
        return ans;
    }
public:
    int numberOfUniqueGoodSubsequences(string binary) {
        int ans = solve(binary);
        for(int i = 0; i < (int)binary.length(); ++i) {
            if(binary[i] != '0')
                continue;
            ans = (ans + mod - solve(binary.substr(i + 1))) % mod;
            break;
        }
        return ans;
    }
};
