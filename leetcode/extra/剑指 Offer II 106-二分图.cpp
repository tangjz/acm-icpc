class Solution {
public:
    bool isBipartite(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<int> col(N);
        for(int i = 0; i < N; ++i) {
            if(col[i] != 0)
                continue;
            queue<int> que;
            auto append = [&](int u, int c) -> bool {
                if(col[u] != 0)
                    return col[u] == c;
                col[u] = c;
                que.push(u);
                return 1;
            };
            append(i, 1);
            while(!que.empty()) {
                int u = que.front(), c = col[u];
                que.pop();
                for(int v : edges[u])
                    if(!append(v, -c))
                        return 0;
            }
        }
        return 1;
    }
};
