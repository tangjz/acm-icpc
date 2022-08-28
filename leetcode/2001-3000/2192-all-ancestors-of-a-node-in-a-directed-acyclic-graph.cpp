class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges)
            e[it[0]].push_back(it[1]);
        vector<vector<int> > ans(n);
        for(int i = 0; i < n; ++i) {
            vector<bool> vis(n);
            queue<int> que;
            vis[i] = 1;
            que.push(i);
            while(!que.empty()) {
                int u = que.front();
                que.pop();
                for(int v: e[u]) {
                    if(vis[v])
                        continue;
                    vis[v] = 1;
                    ans[v].push_back(i);
                    que.push(v);
                }
            }
        }
        return ans;
    }
};
