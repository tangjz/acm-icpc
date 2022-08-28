class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), las = 0, rem = 0;
        queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!grid[i][j])
                    continue;
                ++rem;
                if(grid[i][j] == 2) {
                    que.push({i, j});
                    continue;
                }
            }
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            int d = las = grid[x][y] - 2;
            --rem;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= m || grid[xx][yy] != 1)
                        continue;
                    grid[xx][yy] = 3 + d;
                    que.push({xx, yy});
                }
        }
        return !rem ? las : -1;
    }
};
