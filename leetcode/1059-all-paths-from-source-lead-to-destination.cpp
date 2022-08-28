class Solution {
    bool dfs(int u, int dst, vector<int> &vis, vector<vector<int> > &e) {
        vis[u] = 1;
        for(int v: e[u])
            if((!vis[v] && dfs(v, dst, vis, e)) || vis[v] == 1)
                return 1;
        if(e[u].empty() && u != dst)
            return 1;
        vis[u] = 2;
        return 0;
    }
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        int c = 0;
        vector<int> vis(n);
        vector<vector<int> > e(n);
        for(auto &it: edges)
            e[it[0]].push_back(it[1]);
        return !dfs(source, destination, vis, e);
    }
};
