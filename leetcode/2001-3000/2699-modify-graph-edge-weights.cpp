class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int s, int t, int goal) {
        typedef long long LL;
        const int INF = 0x3f3f3f3f;
        int m = edges.size();
        LL calc_cost = 1;
        for( ; (1LL << calc_cost) <= m; ++calc_cost);
        calc_cost = calc_cost * m - (LL)n * n;
        vector<vector<pair<int, int> > > e(n);
        vector<int> seq;
        for(int i = 0; i < m; ++i) {
            e[edges[i][0]].push_back({edges[i][1], i});
            e[edges[i][1]].push_back({edges[i][0], i});
            if(edges[i][2] == -1) {
                edges[i][2] = INF;
                seq.push_back(i);
            }
        }
        m = seq.size();
        vector<bool> vis(n);
        priority_queue<pair<int, int> > que;
        auto calc = [&](int s, vector<int> &dis) {
            dis.assign(n, INF);
            if(calc_cost >= 0) {
                vis.assign(n, false);
                dis[s] = 0;
                for(int i = 0; i < n; ++i) {
                    int p = -1;
                    for(int u = 0; u < n; ++u)
                        if(!vis[u] && (p == -1 || dis[u] < dis[p]))
                            p = u;
                    if(p == -1 || dis[p] == INF)
                        break;
                    vis[p] = 1;
                    for(auto &it: e[p])
                        dis[it.first] = min(dis[it.first], dis[p] + edges[it.second][2]);
                }
                return;
            }
            auto upd = [&](int u, int d) {
                if(dis[u] > d) {
                    dis[u] = d;
                    que.push({-d, u});
                }
            };
            upd(s, 0);
            while(!que.empty()) {
                pair<int, int> cur = que.top();
                que.pop();
                int u = cur.second, du = dis[u];
                if(-cur.first != du)
                    continue;
                for(auto &it: e[u])
                    upd(it.first, du + edges[it.second][2]);
            }
        };
        vector<int> dis0(n);
        calc(s, dis0);
        if(dis0[t] < goal)
            return {};
        int L = 0, R = m + 1;
        while(L < R) {
            int M = (L + R) >> 1;
            for(int i = 0; i < M; ++i)
                edges[seq[i]][2] = 1;
            for(int i = M; i < m; ++i)
                edges[seq[i]][2] = INF;
            calc(s, dis0);
            if(dis0[t] <= goal) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        if(L > m)
            return {};
        for(int i = 0; i < L; ++i)
            edges[seq[i]][2] = 1;
        for(int i = L; i < m; ++i)
            edges[seq[i]][2] = INF;
        if(!L)
            return edges;
        vector<int> dis1(n);
        calc(s, dis0);
        calc(t, dis1);
        int u = edges[seq[L - 1]][0], v = edges[seq[L - 1]][1];
        if(dis0[u] > dis0[v])
            swap(u, v);
        edges[seq[L - 1]][2] = goal - dis0[u] - dis1[v];
        return edges;
    }
};
