class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        typedef long long LL;
        typedef pair<LL, int> Edge;
        vector<vector<Edge> > e(n);
        for(auto &it: roads) {
            int u = it[0], v = it[1];
            LL w = it[2];
            e[u].push_back({w, v});
            e[v].push_back({w, u});
        }
        const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
        const LL INFLL = (LL)INF << 32 | INF;
        vector<int> vis(n);
        vector<Edge> dis(n, {INFLL, 0});
        priority_queue<Edge> que;
        dis[0] = {0LL, 1};
        que.push({-dis[0].first, 0});
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            for(auto &it: e[u]) {
                int v = it.second;
                LL tp = dis[u].first + it.first;
                if(tp < dis[v].first) {
                    dis[v] = {tp, 0};
                    que.push({-dis[v].first, v});
                }
                if(tp == dis[v].first)
                    (dis[v].second += dis[u].second) >= mod && (dis[v].second -= mod);
            }
        }
        return dis[n - 1].second;
    }
};
