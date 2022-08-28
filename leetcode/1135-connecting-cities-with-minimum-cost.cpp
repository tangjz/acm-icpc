class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& e) {
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) -> bool {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return 0;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
            return 1;
        };
        sort(e.begin(), e.end(), [&](auto const &u, auto const &v) {
            return u.back() < v.back();
        });
        int rem = n, sum = 0;
        for(auto &it: e)
            if(dsu_merge(--it[0], --it[1])) {
                --rem;
                sum += it[2];
            }
        return rem == 1 ? sum : -1;
    }
};
