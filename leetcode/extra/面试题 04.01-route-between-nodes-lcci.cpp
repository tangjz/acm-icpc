class Solution {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<vector<int> > e(n);
        for(auto &it: graph)
            e[it[0]].push_back(it[1]);
        vector<bool> vis(n);
        queue<int> que;
        vis[start] = 1;
        que.push(start);
        while(!vis[target] && !que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                if(!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
        }
        return vis[target];
    }
};
