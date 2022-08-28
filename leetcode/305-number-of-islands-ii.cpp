class Solution {
public:
    vector<int> numIslands2(int r, int c, vector<vector<int>>& positions) {
        int n = r * c;
        vector<int> dsu(n, -1), pos(n);
        function<int(int)> dsu_find = [&](int x) {
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
        int cnt = 0;
        vector<int> ans;
        ans.reserve(positions.size());
        for(auto &it: positions) {
            int ux = it[0], uy = it[1], u = ux * c + uy;
            if(!pos[u]) {
                pos[u] = 1;
                ++cnt;
            }
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, v = u + dx * c + dy;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || !pos[v])
                        continue;
                    cnt -= dsu_merge(u, v);
                }
            ans.push_back(cnt);
        }
        return ans;
    }
};
