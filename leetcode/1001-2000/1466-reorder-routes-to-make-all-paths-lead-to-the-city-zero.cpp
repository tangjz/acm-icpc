class Solution {
public:
    int minReorder(int n, vector<vector<int>>& edges) {
        int ret = 0;
        vector<vector<int> > e(n, vector<int>()), re(n, vector<int>());
        for(auto &it : edges) {
            int u = it[0], v = it[1];
            re[u].push_back(v);
            e[v].push_back(u);
        }
        vector<int> vis(n, 0);
        queue<int> que;
        auto append = [&](int u) -> bool {
            if(vis[u])
                return 0;
            vis[u] = 1;
            que.push(u);
            return 1;
        };
        append(0);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : e[u])
                append(v);
            for(int v : re[u])
                ret += append(v);
        }
        return ret;
    }
};
