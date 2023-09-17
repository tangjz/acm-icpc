class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<int> > dp(r, vector<int>(c));
        for(int i = c - 2; i >= 0; --i)
            for(int j = 0; j < r; ++j) {
                int L = max(j - 1, 0), R = min(j + 1, r - 1);
                for(int k = L; k <= R; ++k)
                    if(grid[k][i + 1] > grid[j][i])
                        dp[j][i] = max(dp[j][i], dp[k][i + 1] + 1);
            }
        int ans = 0;
        for(int i = 0; i < r; ++i)
            ans = max(ans, dp[i][0]);
        return ans;
    }
};
