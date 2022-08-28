class Solution {
    vector<int> getFarest(vector<vector<int> > &e, int s) {
        int n = e.size();
        vector<int> pre(n, -1);
        queue<int> que;
        auto upd = [&](int u, int v) {
            if(pre[v] == -1) {
                pre[v] = u;
                que.push(v);
            }
        };
        pre[s] = s;
        que.push(s);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                upd(u, v);
        }
        vector<int> ret;
        for(int u = que.back(); u != s; u = pre[u])
            ret.push_back(u);
        ret.push_back(s);
        reverse(ret.begin(), ret.end());
        return move(ret);
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> path = getFarest(e, 0);
        path = getFarest(e, path.back());
        int m = path.size();
        if(m & 1)
            return {path[m >> 1]};
        return {path[(m - 1) >> 1], path[m >> 1]};
    }
};
