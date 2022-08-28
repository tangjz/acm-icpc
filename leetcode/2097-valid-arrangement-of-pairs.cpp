class Solution {
    void dfs(int u, map<int, set<int> > &e, vector<vector<int> > &sol) {
        while(!e[u].empty()) {
            int v = *e[u].begin();
            e[u].erase(e[u].begin());
            dfs(v, e, sol);
        }
        if(!sol.empty()) {
            sol.back()[0] = u;
        }
        sol.push_back({-1, u});
    }
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        map<int, int> deg;
        map<int, set<int> > e;
        for(auto &it: pairs) {
            int u = it[0];
            int v = it[1];
            e[u].insert(v);
            ++deg[u];
            --deg[v];
        }
        vector<vector<int> > sol;
        for(auto &it: deg) {
            if(it.second > 0) {
                dfs(it.first, e, sol);
                sol.pop_back();
                reverse(sol.begin(), sol.end());
                return sol;
            }
        }
        dfs(deg.begin() -> first, e, sol);
        sol.pop_back();
        reverse(sol.begin(), sol.end());
        return sol;
    }
};
