class Solution {
public:
    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        const int INF = 0x3f3f3f3f;
        typedef long long LL;
        vector<vector<pair<int, int> > > e(n);
        vector<int> dis(n);
        priority_queue<pair<int, int> > que;
        vector<LL> ans(n);
        for(auto &it: roads) {
            e[--it[0]].push_back({it[2], --it[1]});
            e[it[1]].push_back({it[2], it[0]});
        }
        for(int s = 0; s < n; ++s) {
            for( ; !que.empty(); que.pop());
            dis.assign(n, INF);
            dis[s] = 0;
            que.push({-dis[s], s});
            ans[s] = appleCost[s];
            int upp = ans[s] / (k + 1);
            while(!que.empty()) {
                pair<int, int> cur = que.top();
                int u = cur.second;
                que.pop();
                if(-cur.first > upp)
                    break;
                if(-cur.first != dis[u])
                    continue;
                ans[s] = min(ans[s], (k + 1LL) * dis[u] + appleCost[u]);
                for(auto &it: e[u]) {
                    int v = it.second, tmp = dis[u] + it.first;
                    if(dis[v] > tmp) {
                        dis[v] = tmp;
                        que.push({-dis[v], v});
                    }
                }
            }
        }
        return ans;
    }
};
