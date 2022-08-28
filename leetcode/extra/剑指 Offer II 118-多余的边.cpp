class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
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
        for(auto &it: edges)
            if(!dsu_merge(it[0], it[1]))
                return it;
        return {};
    }
};
