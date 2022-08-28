class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        typedef long long LL;
        const LL INF = 0x3f3f3f3f3f3f3f3fLL;
        vector<int> sta = {src1, src2, dest};
        vector<vector<pair<int, int> > > e(n);
        vector<vector<LL>> dis(3, vector<LL>(n, INF));
        for(int i = 0; i < 3; ++i) {
            if(i == 0) {
                for(auto &it: edges)
                    e[it[0]].push_back({it[1], it[2]});
            } else if(i == 2) {
                for(int u = 0; u < n; ++u)
                    e[u].clear();
                for(auto &it: edges)
                    e[it[1]].push_back({it[0], it[2]});
            }
            priority_queue<pair<LL, int> > que;
            vector<bool> vis(n);
            dis[i][sta[i]] = 0;
            que.push({-dis[i][sta[i]], sta[i]});
            while(!que.empty()) {
                int u = que.top().second;
                que.pop();
                if(vis[u])
                    continue;
                vis[u] = 1;
                for(auto &it: e[u]) {
                    int v = it.first;
                    LL w = dis[i][u] + it.second;
                    if(w >= dis[i][v])
                        continue;
                    dis[i][v] = w;
                    que.push({-dis[i][v], v});
                }
            }
        }
        LL ans = INF;
        for(int i = 0; i < n; ++i) {
            if(dis[0][i] == INF || dis[1][i] == INF || dis[2][i] == INF)
                continue;
            ans = min(ans, dis[0][i] + dis[1][i] + dis[2][i]);
        }
        return ans < INF ? ans : -1;
    }
};
