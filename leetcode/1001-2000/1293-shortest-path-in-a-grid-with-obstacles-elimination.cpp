class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        const int INF = 0x3f3f3f3f;
        int n = (int)grid.size(), m = (int)grid[0].size();
        vector<vector<vector<int> > > dis(n, vector<vector<int> >(m, vector<int>(k + 1, INF)));
        queue<vector<int> > que;
        auto append = [&](int x, int y, int z, int dist) {
            if(z > k || dis[x][y][z] < INF)
                return;
            dis[x][y][z] = dist;
            que.push({x, y, z});
        };
        append(0, 0, 0, 0);
        while(!que.empty()) {
            auto &cur = que.front();
            int x = cur[0], y = cur[1], z = cur[2], dist = dis[x][y][z] + 1;
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= m)
                        continue;
                    int zz = z + grid[x][y];
                    append(xx, yy, zz, dist);
                }
        }
        int ans = INF;
        for(int i = 0; i <= k; ++i)
            ans = min(ans, dis[n - 1][m - 1][i]);
        return ans < INF ? ans : -1;
    }
};
