class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        typedef pair<int, int> Edge;
        int r = maze.size(), c = maze[0].size(), n = r * c;
        int s = ball[0] * c + ball[1];
        int t = hole[0] * c + hole[1];
        vector<vector<pair<char, Edge> > > e(n);
        for(int i = 0; i < r; ++i) {
            for(int j = 0, idx = i * c, k = j; j < c; ++j, ++idx) {
                if(idx == t) {
                    k = j;
                    continue;
                }
                if(maze[i][j]) {
                    k = j + 1;
                    continue;
                }
                if(j > k) {
                    int dt = j - k;
                    e[idx - dt].push_back({'l', {dt, idx}});
                }
            }
            for(int j = c - 1, idx = (i + 1) * c - 1, k = j; j >= 0; --j, --idx) {
                if(idx == t) {
                    k = j;
                    continue;
                }
                if(maze[i][j]) {
                    k = j - 1;
                    continue;
                }
                if(j < k) {
                    int dt = k - j;
                    e[idx + dt].push_back({'r', {dt, idx}});
                }
            }
        }
        for(int j = 0; j < c; ++j) {
            for(int i = 0, idx = j, k = i; i < r; ++i, idx += c) {
                if(idx == t) {
                    k = i;
                    continue;
                }
                if(maze[i][j]) {
                    k = i + 1;
                    continue;
                }
                if(i > k) {
                    int dt = i - k;
                    e[idx - dt * c].push_back({'u', {dt, idx}});
                }
            }
            for(int i = r - 1, idx = i * c + j, k = i; i >= 0; --i, idx -= c) {
                if(idx == t) {
                    k = i;
                    continue;
                }
                if(maze[i][j]) {
                    k = i - 1;
                    continue;
                }
                if(i < k) {
                    int dt = k - i;
                    e[idx + dt * c].push_back({'d', {dt, idx}});
                }
            }
        }
        const int INF = 0x3f3f3f3f;
        vector<int> dis(n, INF);
        vector<bool> vis(n);
        priority_queue<Edge> que;
        dis[t] = 0;
        que.push({-dis[t], t});
        while(!que.empty()) {
            int v = que.top().second;
            que.pop();
            if(vis[v])
                continue;
            vis[v] = 1;
            for(auto &jt: e[v]) {
                auto &it = jt.second;
                int u = it.second;
                int tmp = dis[v] + it.first;
                if(dis[u] > tmp) {
                    dis[u] = tmp;
                    que.push({-dis[u], u});
                }
            }
        }
        if(dis[s] == INF)
            return "impossible";
        string ret = "";
        vector<pair<char, int> > nxt(n, {'z', -1});
        for(int v = 0; v < n; ++v) {
            if(dis[v] == INF)
                continue;
            for(auto &jt: e[v]) {
                auto &it = jt.second;
                int u = it.second;
                int tmp = dis[v] + it.first;
                if(dis[u] == tmp)
                    nxt[u] = min(nxt[u], {jt.first, v});
            }
        }
        for(int u = s; u != t; u = nxt[u].second)
            ret.push_back(nxt[u].first);
        return ret;
    }
};
