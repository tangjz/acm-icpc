class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        for(int i = 0; i < n; ++i)
            values.push_back(values[i]);
        vector<vector<int> > dp(n + n, vector<int>(n + n, INT_MAX));
        for(int i = 0; i + 1 < n + n; ++i) {
            dp[i][i + 1] = 0;
        }
        for(int l = 2; l < n; ++l)
            for(int i = 0, j = l; j < n + n; ++i, ++j)
                for(int k = i + 1; k < j; ++k)
                    if(dp[i][k] < INT_MAX && dp[k][j] < INT_MAX)
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + values[i] * values[j] * values[k]);
        int ans = INT_MAX;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < i + n; ++j)
            ans = min(ans, dp[i][j] + dp[j][i + n]);
        return ans;
    }
};
