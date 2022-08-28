class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int> > > e(n);
        vector<int> dis(n, INT_MAX);
        vector<bool> vis(n);
        priority_queue<pair<int, int> > que;
        for(auto &it: edges) {
            e[it[0]].push_back({it[1], it[2] + 1});
            e[it[1]].push_back({it[0], it[2] + 1});
        }
        auto upd = [&](int u, int d) {
            if(dis[u] <= d)
                return;
            dis[u] = d;
            que.push({-d, u});
        };
        upd(0, 0);
        int ans = 0;
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            ans += dis[u] <= maxMoves;
            vis[u] = 1;
            for(auto &it: e[u])
                upd(it.first, dis[u] + it.second);
        }
        for(auto &it: edges) {
            int L = max(maxMoves - dis[it[0]], 0);
            int R = it[2] + 1 - max(maxMoves - dis[it[1]], 0);
            ans += it[2] - max(R - L - 1, 0);
        }
        return ans;
    }
};
