class Solution {
public:
    int minimalSteps(vector<string>& maze) {
        int r = maze.size(), c = maze[0].size(), n = r * c;
        int s = -1, t = -1;
        vector<int> ones;
        vector<vector<int> > e(n);
        for(int i = 0, idx = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++idx) {
                if(maze[i][j] == '#')
                    continue;
                if(i > 0 && maze[i - 1][j] != '#') {
                    e[idx].push_back(idx - c);
                    e[idx - c].push_back(idx);
                }
                if(j > 0 && maze[i][j - 1] != '#') {
                    e[idx].push_back(idx - 1);
                    e[idx - 1].push_back(idx);
                }
                if(maze[i][j] == 'M') {
                    ones.push_back(idx);
                } else if(maze[i][j] == 'S') {
                    s = idx;
                } else if(maze[i][j] == 'T') {
                    t = idx;
                }
            }
        queue<int> que;
        vector<int> dis;
        auto getDist = [&](int rt) {
            vector<int>(n, -1).swap(dis);
            dis[rt] = 0;
            que.push(rt);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int v: e[u])
                    if(dis[v] == -1) {
                        dis[v] = dis[u] + 1;
                        que.push(v);
                    }
            }
        };
        if(ones.empty()) {
            getDist(t);
            return dis[s];
        }
        int m = ones.size(), all = (1 << m) - 1;
        vector<vector<int> > tr(m, vector<int>(m, -1));
        auto mergeDist = [&](int lft, int rht) {
            return lft == -1 || rht == -1 ? -1 : lft + rht;
        };
        auto updDist = [&](int &dst, int src) {
            if(src != -1 && (dst == -1 || dst > src))
                dst = src;
        };
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(maze[i][j] == 'O') {
                    getDist(i * c + j);
                    for(int u = 0; u < m; ++u) {
                        updDist(tr[u][u], mergeDist(dis[s], dis[ones[u]]));
                        for(int v = u + 1; v < m; ++v)
                            updDist(tr[u][v], mergeDist(dis[ones[u]], dis[ones[v]]));
                    }
                }
        vector<vector<int> > dp(m, vector<int>(1 << m, -1));
        for(int u = 0; u < m; ++u) {
            dp[u][1 << u] = tr[u][u];
            for(int v = u + 1; v < m; ++v)
                tr[v][u] = tr[u][v];
        }
        for(int i = 1; i < all; ++i)
            for(int u = 0; u < m; ++u) {
                if(dp[u][i] == -1)
                    continue;
                for(int v = 0; v < m; ++v) {
                    if((i >> v) & 1 || tr[u][v] == -1)
                        continue;
                    updDist(dp[v][i | 1 << v], mergeDist(dp[u][i], tr[u][v]));
                }
            }
        int ans = -1;
        getDist(t);
        for(int u = 0; u < m; ++u)
            updDist(ans, mergeDist(dp[u][all], dis[ones[u]]));
        return ans;
    }
};
