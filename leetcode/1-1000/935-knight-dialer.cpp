class Solution {
public:
    int knightDialer(int n) {
        const int r = 4, c = 3, m = r * c, mod = (int)1e9 + 7;
        vector<bool> ban(r * c);
        ban[9] = ban[11] = 1;
        vector<vector<int> > e(m);
        for(int i = 0; i < m; ++i) {
            if(ban[i])
                continue;
            int ux = i / c, uy = i % c;
            for(int dx = -2; dx <= 2; ++dx)
                for(int dy = -2; dy <= 2; ++dy)
                    if(abs(dx) + abs(dy) == 3) {
                        int vx = ux + dx, vy = uy + dy, j = i + dx * c + dy;
                        if(vx < 0 || vx >= r || vy < 0 || vy >= c || ban[j])
                            continue;
                        e[i].push_back(j);
                    }
        }
        vector<int> f(m);
        for(int i = 0; i < m; ++i)
            f[i] = !ban[i];
        for(int i = 1; i < n; ++i) {
            vector<int> g(m);
            for(int j = 0; j < m; ++j)
                for(int k: e[j])
                    (g[k] += f[j]) >= mod && (g[k] -= mod);
            f = move(g);
        }
        int ans = 0;
        for(int x: f)
            (ans += x) >= mod && (ans -= mod);
        return ans;
    }
};
