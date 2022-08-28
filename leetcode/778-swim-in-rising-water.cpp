class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size(), m = n * n;
        vector<int> pos(m), dsu(m, -1);
        for(int i = 0, idx = 0; i < n; ++i)
            for(int j = 0; j < n; ++j, ++idx)
                pos[grid[i][j]] = idx;
        function<int(int)> dsu_find;
        dsu_find = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u != v) {
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[u] -= dsu[u] == dsu[v];
                dsu[v] = u;
            }
        };
        const int maxd = 4, dx[maxd] = {0, 1, 0, -1}, dy[maxd] = {1, 0, -1, 0};
        for(int i = 0; i < m; ++i) {
            int x = pos[i] / n, y = pos[i] % n;
            for(int j = 0; j < maxd; ++j) {
                int nx = x + dx[j], ny = y + dy[j];
                if(nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] < i)
                    dsu_merge(pos[i], nx * n + ny);
            }
            if(dsu_find(0) == dsu_find(n * n - 1))
                return i;
        }
        return m;
    }
};
