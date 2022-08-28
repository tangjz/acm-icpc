class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        int m = n * n;
        vector<vector<int> > nxt(m);
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < n; ++y) {
                int u = x * n + y;
                for(int dx = -2; dx <= 2; ++dx)
                    for(int dy = -2; dy <= 2; ++dy) {
                        if(abs(dx) == abs(dy) || abs(dx) + abs(dy) != 3)
                            continue;
                        int xx = x + dx, yy = y + dy;
                        if(xx < 0 || xx >= n || yy < 0 || yy >= n)
                            continue;
                        int v = xx * n + yy;
                        nxt[u].push_back(v);
                    }
            }
        vector<double> f(m), g(m);
        if(row < n && column < n)
            f[row * n + column] = 1;
        while(k--) {
            g.assign(m, 0);
            for(int u = 0; u < m; ++u)
                for(int v: nxt[u])
                    g[v] += f[u] / 8;
            f.swap(g);
        }
        double ans = 0;
        for(int u = 0; u < m; ++u)
            ans += f[u];
        return ans;
    }
};
