class Solution {
    int n;
    vector<int> can;
    vector<vector<int> > edges;
    bool reachable(int u) {
        if(can[u] == -1) {
            can[u] = 0;
            for(int v : edges[u])
                if(reachable(v)) {
                    can[u] = 1;
                    break;
                }
        }
        return can[u];
    }
    void dfs(int u, vector<int> &path, vector<vector<int> > &ret) {
        if(!reachable(u))
            return;
        path.push_back(u);
        if(u == n - 1) {
            ret.push_back(path);
        } else {
            for(int v : edges[u])
                dfs(v, path, ret);
        }
        path.pop_back();
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        n = (int)graph.size();
        edges = move(graph);
        can.assign(n, -1);
        can[n - 1] = 1;
        vector<int> path;
        vector<vector<int> > ret;
        dfs(0, path, ret);
        return ret;
    }
};
