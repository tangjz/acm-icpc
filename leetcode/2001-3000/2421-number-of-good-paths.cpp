class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size(), st = 0;
        vector<int> ord(n), rnk(n), dsu(n, -1), tim(n), ctr(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return vals[u] < vals[v];
        });
        for(int i = 0; i < n; ++i)
            rnk[ord[i]] = i;
        int ans = 0;
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            int u = it[0], v = it[1];
            if(rnk[u] > rnk[v])
                swap(u, v);
            e[v].push_back(u);
        }
        function<int(int)> dsuFind = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsuFind(dsu[u]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            if(tim[v] != st) {
                tim[v] = st;
                ctr[v] = 0;
            }
            if(tim[u] == st) {
                ans += ctr[u] * ctr[v];
                ctr[v] += ctr[u];
            }
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
        };
        for(int u: ord) {
            st = max(st, vals[u]);
            int p = dsuFind(u);
            if(tim[p] != st) {
                tim[p] = st;
                ctr[p] = 0;
            }
            ans += ++ctr[p];
            for(int v: e[u])
                dsuMerge(u, v);
        }
        return ans;
    }
};
