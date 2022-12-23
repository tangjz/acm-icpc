class Solution {
    typedef long long LL;
    int dfs(int u, int p, vector<vector<int> > &e, int m, LL &ans) {
        int sz = 1;
        for(int v: e[u]) {
            if(v == p)
                continue;
            sz += dfs(v, u, e, m, ans);
        }
        if(p != -1)
            ans += (sz - 1) / m + 1;
        return sz;
    }
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int m) {
        int n = roads.size() + 1;
        vector<vector<int> > e(n);
        for(auto &it: roads) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        LL ans = 0;
        dfs(0, -1, e, m, ans);
        return ans;
    }
};
