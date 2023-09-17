class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] != 1)
                    continue;
                vector<pair<int, int> > que;
                grid[i][j] = 2;
                que.push_back({i, j});
                for(int k = 0; k < (int)que.size(); ++k) {
                    int x, y;
                    tie(x, y) = que[k];
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!!dx == !!dy)
                                continue;
                            int xx = x + dx, yy = y + dy;
                            if(xx < 0 || xx >= n || yy < 0 || yy >= m || grid[xx][yy] != 1)
                                continue;
                            grid[xx][yy] = 2;
                            que.push_back({xx, yy});
                        }
                }
                ans = max(ans, (int)que.size());
            }
        return ans;
    }
};
