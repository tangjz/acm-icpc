class Solution {
public:
    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int t, int k) {
        int sz = n * (k + 1);
        vector<vector<pair<int, int> > > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back({it[1], it[2]});
            e[it[1]].push_back({it[0], it[2]});
        }
        vector<int> dis(sz, INT_MAX);
        priority_queue<pair<int, int> > que;
        auto upd = [&](int u, int d) {
            if(dis[u] <= d)
                return;
            dis[u] = d;
            que.push({-d, u});
        };
        upd(s, 0);
        while(!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if(dis[u] != -d)
                continue;
            int o = u / n, p = u % n;
            if(p == t)
                return -d;
            for(auto &[q, w]: e[p]) {
                upd(u - p + q, -d + w);
                if(o < k)
                    upd(u - p + q + n, -d);
            }
        }
        return INT_MAX;
    }
};
