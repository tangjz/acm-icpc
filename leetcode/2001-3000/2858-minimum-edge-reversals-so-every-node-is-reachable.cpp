class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<int> f(n), par(n, -1), que;
        vector<vector<int> > e(n);
        for(int i = 0; i < m; ++i) {
            int u = edges[i][0], v = edges[i][1];
            e[u].push_back(i);
            e[v].push_back(i);
        }
        que.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = que[i];
            for(int it: e[u]) {
                int v = edges[it][0] + edges[it][1] - u;
                bool down = edges[it][0] == u;
                if(v == par[u])
                    continue;
                par[v] = u;
                que.push_back(v);
                if(down) {
                    ++f[v];
                } else {
                    ++f[0];
                    --f[v];
                }
            }
        }
        for(int i = 1; i < n; ++i) {
            int u = que[i];
            f[u] += f[par[u]];
        }
        return f;
    }
};
