class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = (int)row.size() >> 1;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find;
        dsu_find = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u != v) {
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[u] -= dsu[u] == dsu[v];
                dsu[v] = u;
            }
        };
        for(int i = 0; i < n << 1; i += 2)
            dsu_merge(row[i] >> 1, row[i + 1] >> 1);
        int ret = 0;
        for(int i = 0; i < n; ++i)
            ret += dsu_find(i) != i;
        return ret;
    }
};
