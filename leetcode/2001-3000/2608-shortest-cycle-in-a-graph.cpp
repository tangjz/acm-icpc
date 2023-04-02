class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        const int INF = 0x3f3f3f3f;
        int m = edges.size();
        vector<vector<int> > e(n);
        int ans = INF;
        vector<int> dis(n), que(n);
        for(int i = 0; i < m; ++i) {
            int s = edges[i][0], t = edges[i][1];
            for(int j = 0; j < n; ++j)
                e[j].clear();
            for(int j = 0; j < m; ++j) {
                if(i == j)
                    continue;
                int u = edges[j][0], v = edges[j][1];
                e[u].push_back(v);
                e[v].push_back(u);
            }
            dis.assign(n, INF);
            dis[s] = 0;
            que[0] = s;
            for(int j = 0, tot = 1; j < tot; ++j) {
                int u = que[j];
                for(int v: e[u]) {
                    if(dis[v] < INF)
                        continue;
                    dis[v] = dis[u] + 1;
                    que[tot++] = v;
                }
            }
            if(dis[t] < INF)
                ans = min(ans, dis[t] + 1);
        }
        return ans < INF ? ans : -1;
    }
};
