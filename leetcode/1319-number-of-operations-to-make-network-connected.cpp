class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if((int)connections.size() < n - 1)
            return -1;
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
            dsu[v] += dsu[u];
            dsu[u] = v;
            return 1;
        };
        int cnt = 0;
        for(auto &it : connections)
            cnt += dsu_merge(it[0], it[1]);
        return n - 1 - cnt;
    }
};
