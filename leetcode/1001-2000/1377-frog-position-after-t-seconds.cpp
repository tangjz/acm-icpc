class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<vector<int> > e(n + 1, vector<int>());
        for(auto &it : edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<pair<int, double> > dist(n + 1, {INT_MAX, 0.0});
        queue<int> que;
        auto append = [&](int u, pair<int, double> dis) {
            if(dist[u].first < n)
                return;
            dist[u] = dis;
            que.push(u);
        };
        append(1, {0, 1.0});
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            pair<int, double> nxt = dist[u];
            ++nxt.first;
            nxt.second *= (int)e[u].size() - (u != 1);
            for(int v : e[u])
                append(v, nxt);
        }
        return dist[target].first == t || (dist[target].first < t && (int)e[target].size() - (target != 1) == 0) ? 1 / dist[target].second : 0.0;
    }
};
