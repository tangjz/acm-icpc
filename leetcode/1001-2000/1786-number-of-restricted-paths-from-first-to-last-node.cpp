class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        typedef pair<int, int> Edge;
        vector<int> dis(n, INT_MAX);
        vector<vector<Edge> > e(n, vector<Edge>());
        priority_queue<Edge> que;
        for(auto &it: edges) {
            --it[0];
            --it[1];
            e[it[0]].push_back({it[2], it[1]});
            e[it[1]].push_back({it[2], it[0]});
        }
        auto upd = [&](int u, int dist) {
            if(dis[u] > dist) {
                dis[u] = dist;
                que.push({-dis[u], u});
            }
        };
        upd(n - 1, 0);
        while(!que.empty()) {
            Edge cur = que.top();
            que.pop();
            if(-cur.first != dis[cur.second])
                continue;
            int u = cur.second;
            for(auto &it: e[u])
                upd(it.second, dis[u] + it.first);
        }
        const int mod = (int)1e9 + 7;
        vector<int> ord(n), dp(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return dis[u] > dis[v];
        });
        dp[0] = 1;
        for(int u: ord) {
            for(auto &it: e[u]) {
                int v = it.second;
                if(dis[v] > dis[u])
                    dp[u] = (dp[u] + dp[v]) % mod;
            }
        }
        return dp[n - 1];
    }
};
