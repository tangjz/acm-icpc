class Solution {
    static const int maxd = 26;
    void dfs(int u, int p, vector<vector<int> > &e, vector<vector<int> > &ctr, string &buf) {
        ++ctr[u][(int)(buf[u] - 'a')];
        for(int v : e[u]) {
            if(v == p)
                continue;
            dfs(v, u, e, ctr, buf);
            for(int i = 0; i < maxd; ++i)
                ctr[u][i] += ctr[v][i];
        }
    }
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int> > e(n, vector<int>()), ctr(n, vector<int>(maxd, 0));
        for(auto &it : edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        dfs(0, -1, e, ctr, labels);
        vector<int> ret;
        for(int i = 0; i < n; ++i)
            ret.push_back(ctr[i][(int)(labels[i] - 'a')]);
        return ret;
    }
};
