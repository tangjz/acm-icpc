class Solution {
public:
    int minScore(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int> > > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back({--it[1], it[2]});
            e[it[1]].push_back({it[0], it[2]});
        }
        int ans = INT_MAX, tot = 0;
        vector<bool> vis(n);
        vector<int> que(n);
        vis[0] = 1;
        que[tot++] = 0;
        for(int i = 0; i < tot; ++i) {
            int u = que[i];
            for(auto &it: e[u]) {
                ans = min(ans, it.second);
                int v = it.first;
                if(!vis[v]) {
                    vis[v] = 1;
                    que[tot++] = v;
                }
            }
        }
        return ans;
    }
};
