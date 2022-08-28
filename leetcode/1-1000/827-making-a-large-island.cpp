class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = n * n, ans = 0;
        vector<int> dsu(m, -1);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if(!grid[i][j])
                    continue;
                if(i > 0 && grid[i - 1][j])
                    dsuMerge(i * n + j, (i - 1) * n + j);
                if(j > 0 && grid[i][j - 1])
                    dsuMerge(i * n + j, i * n + j - 1);
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if(grid[i][j]) {
                    ans = max(ans, -dsu[dsuFind(i * n + j)]);
                    continue;
                }
                int tmp = 1;
                vector<pair<int, int> > vec;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int x = i + dx, y = j + dy;
                        if(x < 0 || x >= n || y < 0 || y >= n || !grid[x][y])
                            continue;
                        int v = dsuFind(x * n + y);
                        vec.push_back({v, -dsu[v]});
                    }
                sort(vec.begin(), vec.end());
                vec.erase(unique(vec.begin(), vec.end()), vec.end());
                for(auto &it: vec)
                    tmp += it.second;
                ans = max(ans, tmp);
            }
        return ans;
    }
};
