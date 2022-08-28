class Solution {
public:
    int securityCheck(vector<int>& capacities, int k) {
        static const int mod = (int)1e9 + 7;
        vector<int> dp(k + 1);
        dp[0] = 1;
        for(int x: capacities) {
            --x;
            for(int i = k; i >= x; --i)
                (dp[i] += dp[i - x]) >= mod && (dp[i] -= mod);
        }
        return dp[k];
    }
};
