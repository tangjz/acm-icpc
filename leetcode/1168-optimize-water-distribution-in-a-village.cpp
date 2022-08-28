class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        for(int i = 0; i < n; ++i)
            pipes.push_back({0, i + 1, wells[i]});
        ++n;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int x) {
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
        int ans = 0;
        sort(pipes.begin(), pipes.end(), [&](auto const &it, auto const &jt) {
            return it[2] < jt[2];
        });
        for(auto &it: pipes)
            if(dsu_merge(it[0], it[1]))
                ans += it[2];
        return ans;
    }
};
