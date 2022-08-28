class Solution {
    bool check(int n, int m, vector<vector<int> > &grid) {
        vector<vector<int> > vis(n, vector<int>(m, 0));
        queue<pair<int, int> > que;
        auto append = [&](int x, int y) {
            if(x < 0 || x >= n || y < 0 || y >= m || !grid[x][y] || vis[x][y])
                return;
            vis[x][y] = 1;
            que.push({x, y});
        };
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(!grid[i][j] || vis[i][j])
                    continue;
                ++cnt;
                if(cnt > 1)
                    return 1;
                append(i, j);
                while(!que.empty()) {
                    int x, y;
                    tie(x, y) = que.front();
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            append(x + dx, y + dy);
                        }
                }
            }
        return cnt != 1;
    }
public:
    int minDays(vector<vector<int>>& grid) {
        int n = (int)grid.size(), m = (int)grid[0].size();
        if(check(n, m, grid))
            return 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if(check(n, m, grid))
                        return 1;
                    grid[i][j] = 1;
                }
        return 2;
    }
};
