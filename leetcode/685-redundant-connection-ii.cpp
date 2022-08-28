class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> par(n + 1), A, B;
        for(auto &it: edges) {
            int u = it[0], v = it[1];
            if(par[v]) {
                A = {par[v], v};
                B = {u, v};
                it = {0, 0};
            } else {
                par[v] = u;
            }
        }
        vector<int> dsu(n + 1, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        for(auto &it: edges) {
            int u = it[0], v = it[1];
            if(!u)
                continue;
            if(!dsu_merge(u, v))
                return A.empty() ? it : A;
        }
        return B;
    }
};
