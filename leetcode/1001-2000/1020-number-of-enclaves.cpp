class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int ans = 0, n = grid.size(), m = grid[0].size();
        queue<pair<int, int> > que;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!grid[i][j])
                    continue;
                ++ans;
                if(!i || i == n - 1 || !j || j == m - 1) {
                    grid[i][j] = 0;
                    que.push({i, j});
                }
            }
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            --ans;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= m || !grid[xx][yy])
                        continue;
                    grid[xx][yy] = 0;
                    que.push({xx, yy});
                }
        }
        return ans;
    }
};
