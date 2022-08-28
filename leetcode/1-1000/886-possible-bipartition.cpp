class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<vector<int> > edges(N, vector<int>());
        for(auto &it : dislikes) {
            int u = it[0] - 1, v = it[1] - 1;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
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
