class Solution {
public:
    long long mostPoints(vector<vector<int>>& seq) {
        typedef long long LL;
        int n = seq.size();
        vector<LL> dp(n + 1);
        for(int i = 0; i < n; ++i) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
            int j = min(i + seq[i][1] + 1, n);
            dp[j] = max(dp[j], dp[i] + seq[i][0]);
        }
        return dp.back();
    }
};
