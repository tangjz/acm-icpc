class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
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
        int rem = n;
        sort(logs.begin(), logs.end());
        for(auto &it: logs) {
            rem -= dsu_merge(it[1], it[2]);
            if(rem == 1)
                return it[0];
        }
        return -1;
    }
};
