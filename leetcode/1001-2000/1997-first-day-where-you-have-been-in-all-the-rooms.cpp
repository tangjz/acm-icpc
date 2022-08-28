class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nxt) {
        const int mod = (int)1e9 + 7;
        int n = nxt.size();
        vector<int> dp(n), psum(n + 1);
        for(int i = 0; i < n; ++i) {
            dp[i] = (psum[i] - psum[nxt[i]] + i - nxt[i] + 1) % mod;
            dp[i] < 0 && (dp[i] += mod);
            psum[i + 1] = (psum[i] + dp[i]) % mod;
        }
        int ans = 0;
        for(int i = 0; i + 1 < n; ++i)
            ans = (ans + dp[i] + 1) % mod;
        return ans;
    }
};
