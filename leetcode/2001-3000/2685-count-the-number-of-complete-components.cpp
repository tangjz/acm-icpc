class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> dsu(n, -1), sz(n);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u != v) {
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[v] += dsu[u];
                dsu[u] = v;
            }
            ++sz[v];
        };
        for(auto &it: edges)
            dsuMerge(it[0], it[1]);
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if(dsuFind(i) != i)
                continue;
            ans += -dsu[i] * (-dsu[i] - 1) / 2 == sz[i];
        }
        return ans;
    }
};
