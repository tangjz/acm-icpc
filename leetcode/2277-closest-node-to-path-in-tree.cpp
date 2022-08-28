class Solution {
public:
    vector<int> closestNode(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<int> par(n, -1), dep(n), ord;
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        ord.push_back(0);
        for(int i = 0; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u])
                if(v != par[u]) {
                    par[v] = u;
                    dep[v] = dep[u] + 1;
                    ord.push_back(v);
                }
        }
        vector<int> ret;
        for(auto &it: query) {
            int u = it[0], v = it[1], w = it[2];
            while(u != v && u != w && v != w) {
                if(dep[u] < dep[v])
                    swap(u, v);
                if(dep[u] < dep[w]) {
                    w = par[w];
                    continue;
                }
                u = par[u];
            }
            ret.push_back(u == v ? u : (u == w ? u : v));
        }
        return ret;
    }
};
