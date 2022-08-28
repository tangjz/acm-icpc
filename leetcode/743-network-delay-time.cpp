class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<int> dis(n, INT_MAX), vis(n);
        vector<vector<pair<int, int> > > e(n);
        priority_queue<pair<int, int> > que;
        for(auto &it: times)
            e[--it[0]].push_back({--it[1], it[2]});
        int ans = dis[--k] = 0;
        que.push({-dis[k], k});
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            ans = dis[u];
            --n;
            for(auto &it: e[u]) {
                int v = it.first;
                int tmp = dis[u] + it.second;
                if(tmp < dis[v]) {
                    dis[v] = tmp;
                    que.push({-dis[v], v});
                }
            }
        }
        return n ? -1 : ans;
    }
};
