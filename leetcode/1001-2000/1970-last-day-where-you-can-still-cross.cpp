class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int n = row * col;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int x, int y) -> bool {
            x = dsu_find(x);
            y = dsu_find(y);
            if(x == y)
                return 0;
            if(dsu[x] < dsu[y])
                swap(x, y);
            dsu[y] -= dsu[x] == dsu[y];
            dsu[x] = y;
            return 1;
        };
        auto get_idx = [&](int x, int y) -> int {
            return x >= 0 && x < row && y >= 0 && y < col ? x * col + y : -1;
        };
        int S = get_idx(0, 0), T = get_idx(0, col - 1);
        for(int i = 1; i < row; ++i) {
            dsu_merge(S, get_idx(i, 0));
            dsu_merge(T, get_idx(i, col - 1));
        }
        vector<bool> vis(n);
        for(int i = 0; i < n; ++i) {
            int x = cells[i][0] - 1, y = cells[i][1] - 1, u = get_idx(x, y);
            vis[u] = 1;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    int v = get_idx(x + dx, y + dy);
                    if(v == -1 || !vis[v])
                        continue;
                    dsu_merge(u, v);
                }
            if(dsu_find(S) == dsu_find(T))
                return i;
        }
        return -1;
    }
};
