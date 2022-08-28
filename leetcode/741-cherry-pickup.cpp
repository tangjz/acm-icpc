class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int> > dp(n + 1, vector<int>(n + 1, -1));
        dp[0][0] = grid[0][0];
        for(int len = 1; len <= (n - 1) * 2; ++len) {
            int low = max(len - (n - 1), 0), upp = min(len, n - 1);
            for(int i = upp; i >= low; --i)
                for(int j = upp; j >= low; --j) {
                    int pos[4] = {i, len - i, j, len - j};
                    if(grid[pos[0]][pos[1]] == -1 || grid[pos[2]][pos[3]] == -1) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int best = -1;
                    for(int x = 0; x < 2; ++x) {
                        if(!(x ? pos[1] : pos[0]))
                            continue;
                        for(int y = 0; y < 2; ++y) {
                            if(!(y ? pos[3] : pos[2]))
                                continue;
                            best = max(best, dp[i - !x][j - !y]);
                        }
                    }
                    dp[i][j] = best;
                    if(dp[i][j] == -1)
                        continue;
                    dp[i][j] += grid[pos[0]][pos[1]];
                    if(i != j)
                        dp[i][j] += grid[pos[2]][pos[3]];
                }
        }
        return max(dp[n - 1][n - 1], 0);
    }
};
