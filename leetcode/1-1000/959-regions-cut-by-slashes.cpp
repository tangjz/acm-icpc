class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size(), m = n * n * 4;
        vector<int> dsu(m, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        for(int i = 0, u = 0; i < n; ++i)
            for(int j = 0; j < n; ++j, ++u) {
                if(i > 0) {
                    m -= dsu_merge(u << 2, (u - n) << 2 | 2);
                }
                if(j > 0) {
                    m -= dsu_merge(u << 2 | 3, (u - 1) << 2 | 1);
                }
                if(grid[i][j] != '/') {
                    m -= dsu_merge(u << 2, u << 2 | 1);
                    m -= dsu_merge(u << 2 | 2, u << 2 | 3);
                }
                if(grid[i][j] != '\\') {
                    m -= dsu_merge(u << 2, u << 2 | 3);
                    m -= dsu_merge(u << 2 | 1, u << 2 | 2);
                }
            }
        return m;
    }
};
