class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        const int maxd = 101;
        int r = grid.size(), c = grid[0].size();
        static bitset<maxd> dp[maxd][maxd];
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                dp[i][j].reset();
                if(!i && !j) {
                    dp[i][j].set(0);
                } else {
                    if(i)
                        dp[i][j] |= dp[i - 1][j];
                    if(j)
                        dp[i][j] |= dp[i][j - 1];
                }
                if(grid[i][j] == '(') {
                    dp[i][j] <<= 1;
                } else {
                    dp[i][j] >>= 1;
                }
            }
        return dp[r - 1][c - 1].test(0);
    }
};
