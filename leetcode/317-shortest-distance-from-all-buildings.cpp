class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        const int INF = 0x3f3f3f3f;
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> f(n);
        queue<int> que;
        for(int i = 0, s = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++s) {
                if(grid[i][j])
                    f[s] = INF;
                if(grid[i][j] != 1)
                    continue;
                vector<int> dis(n, INF);
                dis[s] = 0;
                que.push(s);
                while(!que.empty()) {
                    int u = que.front(), ux = u / c, uy = u % c;
                    que.pop();
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int vx = ux + dx, vy = uy + dy, v = u + dx * c + dy;
                            if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] || dis[v] < INF)
                                continue;
                            dis[v] = dis[u] + 1;
                            que.push(v);
                        }
                }
                for(int u = 0; u < n; ++u)
                    (f[u] += dis[u]) >= INF && (f[u] = INF);
            }
        int s = min_element(f.begin(), f.end()) - f.begin();
        return f[s] < INF ? f[s] : -1;
    }
};
