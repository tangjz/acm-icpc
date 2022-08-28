class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        int m = (int)edges.size();
        vector<vector<pair<double, int> > > e(n, vector<pair<double, int> >());
        for(int i = 0; i < m; ++i) {
            auto &it = edges[i];
            double prb = succProb[i];
            if(!prb)
                continue;
            prb = log(prb);
            e[it[0]].push_back({prb, it[1]});
            e[it[1]].push_back({prb, it[0]});
        }
        vector<int> vis(n), hit(n);
        vector<double> dis(n);
        priority_queue<pair<double, int> > que;
        auto append = [&](int v, double dist) {
            if(!hit[v] || dis[v] < dist) {
                hit[v] = 1;
                que.push({dis[v] = dist, v});
            }
        };
        append(start, 0);
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            double pre = dis[u];
            for(auto &it : e[u])
                append(it.second, pre + it.first);
        }
        return hit[end] ? exp(dis[end]) : 0;
    }
};
