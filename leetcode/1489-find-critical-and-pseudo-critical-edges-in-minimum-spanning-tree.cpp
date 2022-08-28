class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = (int)edges.size();
        vector<int> ord;
        for(int i = 0; i < m; ++i)
            ord.push_back(i);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return edges[u][2] < edges[v][2];
        });
        auto getMST = [&](int sp = -1) {
            int cnt = 0, sum = 0;
            vector<int> dsu(n, -1);
            function<int(int)> dsu_find = [&](int u) {
                return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
            };
            for(int id : ord) {
                if(id == sp)
                    continue;
                auto &it = edges[id];
                int u = dsu_find(it[0]), v = dsu_find(it[1]);
                if(u == v)
                    continue;
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[v] += dsu[u];
                dsu[u] = v;
                ++cnt;
                sum += it[2];
            }
            return cnt == n - 1 ? sum : INT_MAX;
        };
        int best = getMST();
        vector<int> typ(m, 0);
        for(int i = 0; i < m; ++i)
            if(best != getMST(i))
                typ[i] |= 2;
        vector<int> dsu(n, -1);
        function<int(int)> dsu_find = [&](int u) {
            return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
        };
        for(int i = 0, j; i < m; ) {
            for(j = i; j < m && edges[ord[i]][2] == edges[ord[j]][2]; ++j)
                if(dsu_find(edges[ord[j]][0]) != dsu_find(edges[ord[j]][1]))
                    typ[ord[j]] |= 1;
            for( ; i < j; ++i) {
                auto &it = edges[ord[i]];
                int u = dsu_find(it[0]), v = dsu_find(it[1]);
                if(u == v)
                    continue;
                if(dsu[u] < dsu[v])
                    swap(u, v);
                dsu[v] += dsu[u];
                dsu[u] = v;
            }
        }
        vector<vector<int> > ret(2, vector<int>());
        for(int i = 0; i < m; ++i)
            if(typ[i] & 2) {
                ret[0].push_back(i);
            } else if(typ[i] & 1) {
                ret[1].push_back(i);
            }
        return ret;
    }
};
