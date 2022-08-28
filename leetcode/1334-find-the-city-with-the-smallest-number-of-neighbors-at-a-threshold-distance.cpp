class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        const int INF = 0x3f3f3f3f;
        vector<vector<int> > dis(n, vector<int>(n, INF));
        for(int i = 0; i < n; ++i)
            dis[i][i] = 0;
        for(auto &it : edges) {
            int u = it[0], v = it[1], w = it[2];
            dis[u][v] = dis[v][u] = min(dis[u][v], w);
        }
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        int pos = -1, best = n + 1;
        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            for(int j = 0; j < n; ++j)
                cnt += dis[i][j] <= distanceThreshold;
            best = min(best, cnt);
            if(best == cnt)
                pos = i;
        }
        return pos;
    }
};
