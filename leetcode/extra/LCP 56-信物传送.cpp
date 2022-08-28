class Solution {
public:
    int conveyorBelt(vector<string>& mat, vector<int>& start, vector<int>& end) {
        const char *pat = "^v<>";
        const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1}, INF = 0x3f3f3f3f;
        int r = mat.size(), c = mat[0].size(), n = r * c, t = end[0] * c + end[1];
        vector<int> dis(n, INF);
        vector<bool> vis(n);
        priority_queue<pair<int, int> > que;
        auto upd = [&](int x, int y, int d) {
            int u = x * c + y;
            if(x < 0 || x >= r || y < 0 || y >= c || dis[u] <= d)
                return;
            dis[u] = d;
            que.push({-d, u});
        };
        upd(start[0], start[1], 0);
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            int x = u / c, y = u % c, d = dis[u];
            if(u == t)
                return d;
            for(int i = 0; i < 4; ++i)
                upd(x + dx[i], y + dy[i], d + (mat[x][y] != pat[i]));
        }
        return -1;
    }
};
