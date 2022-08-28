class Solution {
public:
    int longestIdealString(string s, int k) {
        const int maxd = 26;
        vector<int> dp(maxd);
        for(char ch: s) {
            int o = ch - 'a';
            int L = max(o - k, 0), R = min(o + k, maxd - 1);
            int upp = *max_element(dp.begin() + L, dp.begin() + R + 1);
            dp[o] = upp + 1;
        }
        return *max_element(dp.begin(), dp.end());
    }
};
