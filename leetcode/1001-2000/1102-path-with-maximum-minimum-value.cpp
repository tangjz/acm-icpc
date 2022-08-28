class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size(), n = r * c;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 1;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        vector<pair<int, int> > que;
        que.reserve(n);
        for(int i = 0, x = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++x)
                que.push_back({-grid[i][j], x});
        sort(que.begin(), que.end());
        int low = min(grid[0][0], grid[r - 1][c - 1]);
        for(auto &it: que) {
            int w = -it.first, u = it.second, ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] < w)
                        continue;
                    dsu_merge(u, u + dx * c + dy);
                }
            if(w <= low && dsu_find(0) == dsu_find(n - 1))
                return w;
        }
        return -1;
    }
};
