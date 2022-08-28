class Solution {
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        vector<int> dis(n, -1), deg(n);
        queue<int> que;
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        for(int i = 0; i < n; ++i) {
            deg[i] = e[i].size();
            if(deg[i] == 1)
                que.push(i);
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                if(deg[v] > 1) {
                    --deg[v];
                    if(deg[v] == 1)
                        que.push(v);
                }
        }
        for(int i = 0; i < n; ++i)
            if(deg[i] > 1) {
                dis[i] = 0;
                que.push(i);
            }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                if(dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
        }
        return dis;
    }
};
