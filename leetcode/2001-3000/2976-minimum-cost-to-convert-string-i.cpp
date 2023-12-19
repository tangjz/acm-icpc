class Solution {
public:
    long long minimumCost(string s, string t, vector<char>& qu, vector<char>& qv, vector<int>& qw) {
        typedef long long LL;
        int m = qu.size();
        vector<vector<int> > edges;
        for(int i = 0; i < m; ++i) {
            int u = qu[i] - 'a', v = qv[i] - 'a';
            edges.push_back({u, v, qw[i]});
        }
        static const int INF = 0x3f3f3f3f, maxn = 209, maxm = 1009;
        int n = 26;
        static int dis[maxn][maxn];
        for(int i = 0; i < n; ++i) {
            memset(dis[i], 0x3f, n * sizeof(int));
            dis[i][i] = 0;
        }
        for(auto &it: edges) {
            int u = it[0], v = it[1], w = it[2];
            // printf("%d->%d: %d\n", u, v, w);
            dis[u][v] = min(dis[u][v], w);
        }
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i) if(dis[i][k] < INF)
                for(int j = 0; j < n; ++j) if(dis[k][j] < INF)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        m = s.size();
        LL ans = 0;
        for(int i = 0; i < m; ++i) {
            if(s[i] == t[i])
                continue;
            int u = s[i] - 'a', v = t[i] - 'a';
            if(dis[u][v] == INF)
                return -1;
            ans += dis[u][v];
        }
        return ans;
    }
};
