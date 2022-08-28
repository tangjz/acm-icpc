class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        typedef long long LL;
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(auto &it: edges)
            dsuMerge(it[0], it[1]);
        long long ans = n * (n - 1LL);
        for(int i = 0; i < n; ++i)
            if(dsuFind(i) == i)
                ans -= -dsu[i] * (-dsu[i] - 1LL);
        return ans / 2;
    }
};
