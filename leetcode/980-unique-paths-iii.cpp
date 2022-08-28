class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = 0;
        int sx = -1, sy = -1;
        int tx = -1, ty = -1;
        vector<vector<int> > nxt;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(grid[i][j] == 1) {
                    grid[i][j] = -1;
                    sx = i;
                    sy = j;
                } else if(grid[i][j] == 2) {
                    grid[i][j] = -1;
                    tx = i;
                    ty = j;
                }
                if(grid[i][j] == -1)
                    continue;
                grid[i][j] = n++;
                nxt.push_back({});
                if(i > 0 && grid[i - 1][j] >= 0) {
                    nxt[grid[i][j]].push_back(grid[i - 1][j]);
                    nxt[grid[i - 1][j]].push_back(grid[i][j]);
                }
                if(j > 0 && grid[i][j - 1] >= 0) {
                    nxt[grid[i][j]].push_back(grid[i][j - 1]);
                    nxt[grid[i][j - 1]].push_back(grid[i][j]);
                }
            }
        if(!n)
            return abs(sx - tx) + abs(sy - ty) == 1;
        int m = 1 << n;
        vector<vector<int> > dp(m, vector<int>(n));
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!dx == !dy)
                    continue;
                int x = sx + dx, y = sy + dy;
                if(x >= 0 && x < r && y >= 0 && y < c && grid[x][y] >= 0) {
                    int i = grid[x][y];
                    dp[1 << i][i] = 1;
                }
            }
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                if(!dp[i][j])
                    continue;
                for(int jj: nxt[j]) {
                    if((i >> jj) & 1)
                        continue;
                    int ii = i | (1 << jj);
                    dp[ii][jj] += dp[i][j];
                }
            }
        int ans = 0;
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!dx == !dy)
                    continue;
                int x = tx + dx, y = ty + dy;
                if(x >= 0 && x < r && y >= 0 && y < c && grid[x][y] >= 0) {
                    int i = grid[x][y];
                    ans += dp[m - 1][i];
                }
            }
        return ans;
    }
};
