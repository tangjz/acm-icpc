class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<int> dsu(n, -1), ord(n);
        function<int(int)> dsu_find = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        iota(ord.begin(), ord.end(), 0);
        for(int i = 0; i < 2; ++i) {
            sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
                return stones[u][i] < stones[v][i];
            });
            for(int j = 0, k = 0; j < n; j = k)
                for(++k; k < n && stones[ord[j]][i] == stones[ord[k]][i]; ++k)
                    dsu_merge(ord[j], ord[k]);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            if(dsu_find(i) == i)
                ans += -dsu[i] - 1;
        return ans;
    }
};
