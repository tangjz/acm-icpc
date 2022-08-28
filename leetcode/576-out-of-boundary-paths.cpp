class Solution {
public:
    int findPaths(int r, int c, int k, int sx, int sy) {
        const int mod = (int)1e9 + 7;
        int ans = 0, n = r * c;
        vector<int> f(n), g(n);
        f[sx * c + sy] = 1;
        auto mod_inc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        while(k--) {
            for(int x = 0, i = 0; x < r; ++x)
                for(int y = 0; y < c; ++y, ++i) {
                    if(!f[i])
                        continue;
                    for(int dx = -1; dx <= 1; ++dx)
                        for(int dy = -1; dy <= 1; ++dy) {
                            if(!dx == !dy)
                                continue;
                            int xx = x + dx, yy = y + dy, j = i + dx * c + dy;
                            if(xx < 0 || xx >= r || yy < 0 || yy >= c) {
                                mod_inc(ans, f[i]);
                            } else {
                                mod_inc(g[j], f[i]);
                            }
                        }
                }
            f.swap(g);
            if(k > 0) {
                g.clear();
                g.resize(n);
            }
        }
        return ans;
    }
};
