class Solution {
    vector<vector<int> > bfs(vector<vector<int> > &grid) {
        const int INF = (int)1e9;
        int r = grid.size(), c = grid[0].size();
        vector<vector<int> > dis(r, vector<int>(c, INF));
        queue<int> que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c || grid[x][y] == 2 || dis[x][y] != INF)
                return;
            dis[x][y] = d;
            que.push(x * c + y);
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(grid[i][j] == 1)
                    upd(i, j, 0);
        while(!que.empty()) {
            int u = que.front(), ux = u / c, uy = u % c;
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy)
                    if(!dx != !dy)
                        upd(ux + dx, uy + dy, dis[ux][uy] + 1);
        }
        return dis;
    }
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        const int INF = (int)1e9;
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<vector<int> > dis1 = bfs(grid);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(grid[i][j] == 1)
                    grid[i][j] = 0;
        grid[0][0] = 1;
        vector<vector<int> > dis2 = bfs(grid);
        vector<int> val(n), seq;
        dis1[r - 1][c - 1] = min(dis1[r - 1][c - 1] + 1, INF);
        for(int i = 0, idx = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++idx) {
                // printf("%d %d: %d %d\n", i, j, dis1[i][j], dis2[i][j]);
                if(grid[i][j] == 2 || dis1[i][j] <= dis2[i][j]) {
                    val[idx] = -1;
                    continue;
                }
                val[idx] = dis1[i][j] == INF ? INF : dis1[i][j] - dis2[i][j] - 1;
                seq.push_back(idx);
            }
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
        };
        sort(seq.begin(), seq.end(), [&](int const &u, int const &v) {
            return val[u] > val[v];
        });
        for(int i = 0; i < (int)seq.size(); ++i) {
            int u = seq[i], ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, v = u + dx * c + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || val[v] < val[u])
                        continue;
                    dsu_merge(u, v);
                }
            if(val[0] >= val[u] && val[n - 1] >= val[u] && dsu_find(0) == dsu_find(n - 1))
                return val[u];
        }
        return -1;
    }
};
