class Solution {
public:
    int minimumDistance(int n, vector<vector<int>>& edges, int s, vector<int>& marked) {
        vector<int> dis(n, INT_MAX);
        vector<vector<pair<int, int> > > e(n);
        priority_queue<pair<int, int> > que;
        for(auto &it: edges)
            e[it[1]].push_back({it[0], it[2]});
        auto upd = [&](int u, int d) {
            if(dis[u] <= d)
                return;
            dis[u] = d;
            que.push({-d, u});
        };
        for(int t: marked)
            upd(t, 0);
        while(!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if(dis[u] != -d)
                continue;
            if(u == s)
                return -d;
            for(auto &[v, w]: e[u])
                upd(v, -d + w);
        }
        return -1;
    }
};
