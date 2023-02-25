class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if(grid[0][1] > 1 && grid[1][0] > 1)
            return -1;
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> dis(n, INT_MAX);
        priority_queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c)
                return;
            int u = x * c + y;
            if(d < grid[x][y])
                d += ((grid[x][y] - d + 1) >> 1) << 1;
            if(dis[u] > d) {
                dis[u] = d;
                que.push({-d, u});
            }
        };
        upd(0, 0, 0);
        while(!que.empty()) {
            pair<int, int> cur = que.top();
            que.pop();
            int u = cur.second, d = dis[u];
            if(-cur.first != d)
                continue;
            int x = u / c, y = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy)
                    if(!dx != !dy)
                        upd(x + dx, y + dy, d + 1);
        }
        return dis[n - 1] < INT_MAX ? dis[n - 1] : -1;
    }
};
