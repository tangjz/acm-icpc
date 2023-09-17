class Solution {
public:
    int challengeOfTheKeeper(vector<string>& g) {
        const int INF = 0x3f3f3f3f;
        int r = g.size(), c = g[0].size(), n = r * c;
        int sx = -1, sy = -1, tx = -1, ty = -1;
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(g[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if(g[i][j] == 'T') {
                    tx = i;
                    ty = j;
                }
        int mx = 0, s = sx * c + sy, t = tx * c + ty;
        vector<int> dis(n, INF), upp(n);
        queue<int> que;
        auto upd = [&](int u, int d) {
            if(dis[u] <= d)
                return;
            mx = max(mx, d);
            dis[u] = d;
            que.push(u);
        };
        upd(t, 0);
        while(!que.empty()) {
            int u = que.front(), ux = u / c, uy = u % c;
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || g[vx][vy] == '#')
                        continue;
                    upd(vx * c + vy, dis[u] + 1);
                }
        }
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(g[i][j] == '#')
                    continue;
                int u = i * c + j;
                if(g[r - 1 - i][j] == '.') {
                    int v = (r - 1 - i) * c + j;
                    upp[v] = max(upp[v], dis[u]);
                }
                if(g[i][c - 1 - j] == '.') {
                    int v = i * c + (c - 1 - j);
                    upp[v] = max(upp[v], dis[u]);
                }
            }
        vector<vector<int> > lim(mx + 1);
        lim[0].push_back(s);
        lim[0].push_back(t);
        for(int i = 0, u = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++u) {
                // if(g[i][j] == '.') {
                //     printf("%d%c", upp[u], " \n"[j == c - 1]);
                // } else {
                //     printf("%c%c", g[i][j], " \n"[j == c - 1]);
                // }
                if(g[i][j] != '.' || upp[u] == INF)
                    continue;
                lim[upp[u]].push_back(u);
            }
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = 0; i <= mx; ++i)
            for(int u: lim[i]) {
                int ux = u / c, uy = u % c;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!!dx == !!dy)
                            continue;
                        int vx = ux + dx, vy = uy + dy;
                        if(vx < 0 || vx >= r || vy < 0 || vy >= c || g[vx][vy] == '#')
                            continue;
                        int v = u + dx * c + dy;
                        if(upp[v] <= i)
                            dsu_merge(u, v);
                        if(dsu_find(s) == dsu_find(t))
                            return i;
                    }
            }
        return -1;
    }
};
