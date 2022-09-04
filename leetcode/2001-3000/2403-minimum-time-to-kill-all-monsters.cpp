class Solution {
public:
    long long minimumTime(vector<int>& power) {
        typedef long long LL;
        const LL INF = 0x3f3f3f3f3f3f3f3fLL;
        int n = power.size();
        vector<vector<int> > g(n, vector<int>(n));
        vector<int> match(n, -1);
        vector<LL> lx(n, -INF), ly(n), slack(n);
        vector<bool> sx(n), sy(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                g[i][j] = -((power[i] - 1) / (j + 1) + 1);
                lx[i] = max(lx[i], (LL)g[i][j]);
            }
        function<bool(int)> path = [&](int u) -> bool {
            sx[u] = 1;
            for(int v = n - 1; v >= 0; --v) {
                if(sy[v])
                    continue;
                LL dt = lx[u] + ly[v] - g[u][v];
                if(!dt) {
                    sy[v] = 1;
                    if(match[v] == -1 || path(match[v])) {
                        match[v] = u;
                        return 1;
                    }
                } else {
                    slack[v] = min(slack[v], dt);
                }
            }
            return 0;
        };
        for(int i = 0; i < n; ++i) {
            slack.assign(n, INF);
            while(1) {
                sx.assign(n, false);
                sy.assign(n, false);
                if(path(i))
                    break;
                LL dx = INF;
                for(int j = 0; j < n; ++j)
                    if(!sy[j])
                        dx = min(dx, slack[j]);
                for(int j = 0; j < n; ++j) {
                    if(sx[j])
                        lx[j] -= dx;
                    if(sy[j]) {
                        ly[j] += dx;
                    } else {
                        slack[j] -= dx;
                    }
                }
            }
        }
        LL ans = 0;
        for(int i = 0; i < n; ++i)
            ans += g[match[i]][i];
        return -ans;
    }
};
