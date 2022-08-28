class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size(), mx = 0;
        queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(grid[i][j])
                    que.push({i, j});
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            mx = max(mx, grid[x][y]);
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= n || grid[xx][yy]) {
                        continue;
                    }
                    grid[xx][yy] = grid[x][y] + 1;
                    que.push({xx, yy});
                }
        }
        return mx <= 1 ? -1 : mx - 1;
    }
};
