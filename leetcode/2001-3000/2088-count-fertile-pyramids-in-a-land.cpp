class Solution {
    int solve(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size(), ans = 0;
        vector<vector<int> > dp(n, vector<int>(m));
        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j < m; ++j) {
                if(!mat[i][j])
                    continue;
                if(i + 1 >= n || j - 1 < 0 || j + 1 >= m) {
                    dp[i][j] = 1;
                    continue;
                }
                dp[i][j] = min(dp[i + 1][j - 1], min(dp[i + 1][j], dp[i + 1][j + 1])) + 1;
                ans += dp[i][j] - 1;
                // printf("dp %d %d: %d\n", i, j, dp[i][j]);
            }
        }
        // puts("");
        return ans;
    }
public:
    int countPyramids(vector<vector<int>>& grid) {
        int ans = solve(grid);
        reverse(grid.begin(), grid.end());
        ans += solve(grid);
        // puts("");
        return ans;
    }
};
