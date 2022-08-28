class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        typedef pair<int, int> Edge;
        int r = maze.size(), c = maze[0].size(), n = r * c;
        int s = start[0] * c + start[1];
        int t = destination[0] * c + destination[1];
        vector<vector<Edge> > e(n);
        for(int i = 0; i < r; ++i) {
            for(int j = 0, idx = i * c, k = j; j < c; ++j, ++idx) {
                if(maze[i][j]) {
                    k = j + 1;
                    continue;
                }
                if(j > k) {
                    int dt = j - k;
                    e[idx - dt].push_back({dt, idx});
                }
            }
            for(int j = c - 1, idx = (i + 1) * c - 1, k = j; j >= 0; --j, --idx) {
                if(maze[i][j]) {
                    k = j - 1;
                    continue;
                }
                if(j < k) {
                    int dt = k - j;
                    e[idx + dt].push_back({dt, idx});
                }
            }
        }
        for(int j = 0; j < c; ++j) {
            for(int i = 0, idx = j, k = i; i < r; ++i, idx += c) {
                if(maze[i][j]) {
                    k = i + 1;
                    continue;
                }
                if(i > k) {
                    int dt = i - k;
                    e[idx - dt * c].push_back({dt, idx});
                }
            }
            for(int i = r - 1, idx = i * c + j, k = i; i >= 0; --i, idx -= c) {
                if(maze[i][j]) {
                    k = i - 1;
                    continue;
                }
                if(i < k) {
                    int dt = k - i;
                    e[idx + dt * c].push_back({dt, idx});
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
            for(auto &it: e[v]) {
                int u = it.second;
                int nxt = dis[v] + it.first;
                if(dis[u] > nxt) {
                    dis[u] = nxt;
                    que.push({-dis[u], u});
                }
            }
        }
        return dis[s] < INF ? dis[s] : -1;
    }
};
