class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& mat) {
        int m = mat.size(), n = m * m;
        queue<pair<int, int> > que;
        vector<vector<pair<int, int> > > sp = {{}, {}};
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= m || y < 0 || y >= m || mat[x][y])
                return;
            mat[x][y] = d;
            que.push({x, y});
            if(d >= sp.size())
                sp.resize(d + 1);
            sp[d].push_back({x, y});
        };
        for(int x = 0; x < m; ++x)
            for(int y = 0; y < m; ++y)
                if(mat[x][y]) {
                    que.push({x, y});
                    sp[1].push_back({x, y});
                }
        while(!que.empty()) {
            auto &[x, y] = que.front();
            int d = mat[x][y];
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(x + dx, y + dy, d + 1);
                }
            que.pop();
        }
        vector<int> dsu(n, -1);
        vector<bool> vis(n);
        function<int(int)> dsuFind = [&](int u) -> int {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto chk = [&](int x, int y, int u) {
            if(x < 0 || x >= m || y < 0 || y >= m)
                return;
            int v = x * m + y;
            if(!vis[v])
                return;
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = sp.size() - 1; i > 0; --i) {
            for(auto &[x, y]: sp[i]) {
                int u = x * m + y;
                vis[u] = 1;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        chk(x + dx, y + dy, u);
                    }
            }
            if(vis[0] && vis[n - 1] && dsuFind(0) == dsuFind(n - 1))
                return i - 1;
        }
        return -1;
    }
};
