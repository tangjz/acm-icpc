class Solution {
public:
    int minimumSeconds(vector<vector<string>>& land) {
        int r = (int)land.size(), c = (int)land[0].size(), n = r * c, s = -1, t = -1;
        vector<int> d0(n, INT_MAX), d1(n, INT_MAX);
        queue<int> que;
        auto upd = [&](int x, int y, int d) {
            if(x < 0 || x >= r || y < 0 || y >= c || land[x][y][0] != '.')
                return;
            int u = x * c + y;
            if(d0[u] > d) {
                d0[u] = d;
                que.push(u);
            }
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(land[i][j][0] == 'S') {
                    s = i * c + j;
                } else if(land[i][j][0] == 'D') {
                    t = i * c + j;
                } else if(land[i][j][0] == '*') {
                    land[i][j][0] = '.';
                    upd(i, j, 0);
                    land[i][j][0] = '*';
                }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(ux + dx, uy + dy, d0[u] + 1);
                }
        }
        d0.swap(d1);
        land[s / c][s % c] = land[t / c][t % c] = '.';
        upd(s / c, s % c, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(ux + dx, uy + dy, d0[u] + 1);
                }
        }
        for(int i = 0, u = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++u)
                land[i][j][0] = "X."[d0[u] < d1[u]];
        d0.assign(n, INT_MAX);
        upd(s / c, s % c, 0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            if(u == t)
                return d0[u];
            int ux = u / c, uy = u % c;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    upd(ux + dx, uy + dy, d0[u] + 1);
                }
        }
        return -1;
    }
};
