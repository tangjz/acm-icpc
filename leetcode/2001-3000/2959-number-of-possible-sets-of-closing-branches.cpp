class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        const static int maxn = 11, maxs = 1 << 10 | 1, INF = 0x3f3f3f3f;
        int ans = 0;
        for(int s = 0; s < (1 << n); ++s) {
            static int dis[maxn][maxn];
            static bool ban[maxn];
            for(int i = 0; i < n; ++i) {
                ban[i] = (s >> i) & 1;
                memset(dis[i], 0x3f, n * sizeof(int));
                dis[i][i] = ban[i] ? INF : 0;
            }
            for(auto &it: roads) {
                int u = it[0], v = it[1], w = it[2];
                if(ban[u] || ban[v])
                    continue;
                dis[u][v] = dis[v][u] = min(dis[v][u], w);
            }
            for(int k = 0; k < n; ++k) if(!ban[k])
                for(int i = 0; i < n; ++i) if(!ban[i] && dis[i][k] < INF)
                    for(int j = 0; j < n; ++j) if(!ban[j] && dis[k][j] < INF)
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            bool bad = 0;
            for(int i = 0; !bad && i < n; ++i) if(!ban[i])
                for(int j = 0; !bad && j < n; ++j) if(!ban[j])
                    bad |= dis[i][j] > maxDistance;
            ans += !bad;
        }
        return ans;
    }
};
