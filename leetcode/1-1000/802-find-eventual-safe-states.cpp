class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int> > e(n);
        vector<int> deg(n), que;
        for(int i = 0; i < n; ++i) {
            deg[i] = graph[i].size();
            for(int j: graph[i])
                e[j].push_back(i);
            if(!deg[i])
                que.push_back(i);
        }
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int v: e[u])
                if(!(--deg[v]))
                    que.push_back(v);
        }
        sort(que.begin(), que.end());
        return que;
    }
};
