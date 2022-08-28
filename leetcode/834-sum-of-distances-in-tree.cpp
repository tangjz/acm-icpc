class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        vector<int> ord, p(n, -1), c(n), f(n), g(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        ord.reserve(n);
        ord.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(v != p[u]) {
                    p[v] = u;
                    ord.push_back(v);
                }
        }
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i], o = p[u];
            ++c[u];
            if(o >= 0) {
                c[o] += c[u];
                f[o] += f[u] + c[u];
            }
        }
        g[ord[0]] = f[ord[0]];
        for(int i = 1; i < n; ++i) {
            int u = ord[i], o = p[u];
            g[u] = g[o] - c[u] - c[u] + n;
        }
        return g;
    }
};
