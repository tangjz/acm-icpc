class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            e[--it[0]].push_back(--it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<int> que;
        for(int i = 0; i < n; ++i)
            if(e[i].size() & 1)
                que.push_back(i);
        int m = que.size();
        // printf("m: %d\n", m);
        if(m > 4)
            return 0;
        if(!m)
            return 1;
        auto hasEdge = [&](int u, int v) -> bool {
            // printf("chk %d %d\n", u, v);
            for(int x: e[u])
                if(x == v)
                    return 1;
            return 0;
        };
        for(int i = 1; i < m; ++i) {
            if(hasEdge(que[0], que[i]))
                continue;
            if(m == 4) {
                int j = i > 1 ? 1 : 2, k = 6 - i - j;
                if(hasEdge(que[j], que[k]))
                    continue;
            }
            return 1;
        }
        if(m == 2) {
            vector<bool> vis(n);
            for(int i = 0; i < m; ++i) {
                int u = que[i];
                vis[u] = 1;
                for(int v: e[u])
                    vis[v] = 1;
            }
            for(int i = 0; i < n; ++i)
                if(!(e[i].size() & 1) && !vis[i])
                    return 1;
        }
        return 0;
    }
};
