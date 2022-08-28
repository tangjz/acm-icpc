class Solution {
    int dfs(int x, int y, vector<vector<int> > &grid) {
        if(x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || !grid[x][y])
            return 0;
        int best = 0, tmp = grid[x][y];
        grid[x][y] = 0;
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy)
                if(!!dx != !!dy)
                    best = max(best, dfs(x + dx, y + dy, grid));
        grid[x][y] = tmp;
        return best + tmp;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        vector<vector<bool> > vis(n, vector<bool>(m));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(!grid[i][j] || vis[i][j])
                    continue;
                int upp = 0;
                vector<pair<int, int> > que;
                vis[i][j] = 1;
                que.push_back({i, j});
                for(int k = 0; k < (int)que.size(); ++k) {
                    int x, y;
                    tie(x, y) = que[k];
                    upp += grid[x][y];
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!!dx == !!dy)
                                continue;
                            int xx = x + dx, yy = y + dy;
                            if(xx < 0 || xx >= n || yy < 0 || yy >= m || !grid[xx][yy] || vis[xx][yy])
                                continue;
                            vis[xx][yy] = 1;
                            que.push_back({xx, yy});
                        }
                }
                if(ans >= upp)
                    continue;
                for(auto &it: que)
                    ans = max(ans, dfs(it.first, it.second, grid));
            }
        }
        return ans;
    }
};
