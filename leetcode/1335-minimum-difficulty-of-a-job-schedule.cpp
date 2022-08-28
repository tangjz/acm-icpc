class Solution {
public:
    int minDifficulty(vector<int>& a, int d) {
        const int INF = 0x3f3f3f3f;
        int n = (int)a.size();
        if(n < d)
            return -1;
        vector<vector<int> > dp(n + 1, vector<int>(d + 1, INF));
        dp[0][0] = 0;
        for(int i = 0; i < n; ++i) {
            int upp = a[i];
            for(int j = i + 1; j <= n; ++j) {
                upp = max(upp, a[j - 1]);
                for(int k = 1; k <= d; ++k)
                    dp[j][k] = min(dp[j][k], dp[i][k - 1] + upp);
            }
        }
        return dp[n][d];
    }
};
