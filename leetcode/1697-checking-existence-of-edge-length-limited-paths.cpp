class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edges, vector<vector<int>>& que) {
        int m = (int)edges.size(), q = (int)que.size();
        vector<int> ordE(m), ordQ(q);
        iota(ordE.begin(), ordE.end(), 0);
        sort(ordE.begin(), ordE.end(), [&](int const &u, int const &v) {
            return edges[u].back() < edges[v].back();
        });
        iota(ordQ.begin(), ordQ.end(), 0);
        sort(ordQ.begin(), ordQ.end(), [&](int const &u, int const &v) {
            return que[u].back() < que[v].back();
        });
        vector<int> dsu(n, -1);
        function<int(int)> dsuFind = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) -> void {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
        };
        vector<bool> ans(q);
        for(int i = 0, j = 0; i < q; ++i) {
            auto const &it = que[ordQ[i]];
            for( ; j < m && edges[ordE[j]].back() < it.back(); ++j) {
                auto const &jt = edges[ordE[j]];
                dsuMerge(jt[0], jt[1]);
            }
            ans[ordQ[i]] = dsuFind(it[0]) == dsuFind(it[1]);
        }
        return ans;
    }
};
