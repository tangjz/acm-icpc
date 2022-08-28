class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        const int INF = 0x3f3f3f3f;
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> dis(n, INF);
        vector<bool> vis(n);
        priority_queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c)
                return;
            d += grid[x][y] == 1;
            int o = x * c + y;
            if(d < dis[o]) {
                dis[o] = d;
                que.push({-d, o});
            }
        };
        upd(0, 0, 0);
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            int ux = u / c, uy = u % c, ud = dis[u];
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(ux + dx, uy + dy, ud);
                }
        }
        return dis[n - 1];
    }
};
