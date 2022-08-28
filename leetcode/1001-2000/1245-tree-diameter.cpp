class Solution {
    pair<int, int> dfs(int u, int p, vector<vector<int> > &e) {
        pair<int, int> ret = {0, u}, tmp;
        for(int v: e[u]) {
            if(v == p)
                continue;
            tmp = dfs(v, u, e);
            ++tmp.first;
            ret = max(ret, tmp);
        }
        return ret;
    }
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        int u = dfs(0, -1, e).second;
        return dfs(u, -1, e).first;
    }
};
