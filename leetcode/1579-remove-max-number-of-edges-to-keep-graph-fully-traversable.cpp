class Solution {
    int dsu_find(vector<int> &dsu, int x) {
        return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu, dsu[x]));
    }
    bool dsu_merge(vector<int> &dsu, int u, int v) {
        u = dsu_find(dsu, u);
        v = dsu_find(dsu, v);
        if(u == v)
            return 0;
        if(dsu[u] < dsu[v])
            swap(u, v);
        dsu[u] = v;
        --dsu[v];
        return 1;
    }
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int ans = 0;
        vector<int> dsu(n, -1);
        for(auto &it : edges) {
            int typ = it[0], u = it[1] - 1, v = it[2] - 1;
            if(typ != 3)
                continue;
            ans += !dsu_merge(dsu, u, v);
        }
        for(int i = 1; i < 3; ++i) {
            vector<int> dsu_special(dsu.begin(), dsu.end());
            for(auto &it : edges) {
                int typ = it[0], u = it[1] - 1, v = it[2] - 1;
                if(typ != i)
                    continue;
                ans += !dsu_merge(dsu_special, u, v);
            }
            for(int j = 1; j < n; ++j)
                if(dsu_find(dsu_special, j) != dsu_find(dsu_special, 0))
                    return -1;
        }
        return ans;
    }
};
