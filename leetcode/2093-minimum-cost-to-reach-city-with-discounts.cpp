class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        typedef pair<int, int> Node;
        typedef pair<int, int> Edge;
        const int INF = 0x3f3f3f3f;
        vector<vector<Edge> > e(n);
        for(auto &it: highways) {
            e[it[0]].push_back({it[1], it[2]});
            e[it[1]].push_back({it[0], it[2]});
        }
        vector<vector<bool> > vis(n);
        vector<vector<int> > dis(n);
        priority_queue<pair<int, Node> > que;
        auto upd = [&](Node u, int d) {
            if(u.second > discounts)
                return;
            while(u.second >= dis[u.first].size()) {
                dis[u.first].push_back(INF);
                vis[u.first].push_back(0);
            }
            if(dis[u.first][u.second] <= d)
                return;
            dis[u.first][u.second] = d;
            que.push({-d, u});
        };
        upd({0, 0}, 0);
        while(!que.empty()) {
            Node u = que.top().second;
            que.pop();
            if(vis[u.first][u.second])
                continue;
            vis[u.first][u.second] = 1;
            int d = dis[u.first][u.second];
            if(u.first == n - 1)
                return d;
            for(auto &it: e[u.first]) {
                upd({it.first, u.second}, d + it.second);
                upd({it.first, u.second + 1}, d + it.second / 2);
            }
        }
        return -1;
    }
};
