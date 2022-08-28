class Solution {
    int dfs(int u, int p, vector<vector<int> > const &e, int &idx, vector<int> &tim, vector<vector<int> > &ret) {
        int low = tim[u] = ++idx;
        for(int v: e[u]) {
            if(v == p)
                continue;
            if(tim[v]) {
                low = min(low, tim[v]);
                continue;
            }
            int tmp = dfs(v, u, e, idx, tim, ret);
            if(tmp > tim[u])
                ret.push_back({u, v});
            low = min(low, tmp);
        }
        return low;
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int> > e(n);
        for(auto &it: connections) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        int idx = 0;
        vector<int> tim(n);
        vector<vector<int> > ret;
        dfs(0, -1, e, idx, tim, ret);
        return ret;
    }
};
