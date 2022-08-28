class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        vector<vector<int> > e(n);
        vector<int> vis(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        for(int &x: restricted)
            vis[x] = 1;
        vector<int> que;
        auto upd = [&](int u) {
            if(vis[u])
                return;
            que.push_back(u);
            vis[u] = 1;
        };
        upd(0);
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int v: e[u])
                upd(v);
        }
        return que.size();
    }
};
