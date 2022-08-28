class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size(), tot = n * m;
        vector<int> dsu(tot, -1);
        function<int(int)> dsuFind = [&](int x) {
            return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
        };
        auto dsuMerge = [&](int u, int v) {
            u = dsuFind(u);
            v = dsuFind(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] -= dsu[u] == dsu[v];
            dsu[u] = v;
        };
        for(int i = 0; i < n; ++i) {
            unordered_map<int, int> las;
            for(int j = 0; j < m; ++j) {
                auto it = las.find(mat[i][j]);
                if(it != las.end())
                    dsuMerge(i * m + (it -> second), i * m + j);
                las[mat[i][j]] = j;
            }
        }
        for(int j = 0; j < m; ++j) {
            unordered_map<int, int> las;
            for(int i = 0; i < n; ++i) {
                auto it = las.find(mat[i][j]);
                if(it != las.end())
                    dsuMerge((it -> second) * m + j, i * m + j);
                las[mat[i][j]] = i;
            }
        }
        vector<int> deg(tot);
        vector<vector<int> > edges(tot, vector<int>());
        for(int i = 0; i < n; ++i) {
            vector<pair<int, int> > seq;
            for(int j = 0; j < m; ++j)
                seq.push_back({mat[i][j], dsuFind(i * m + j)});
            sort(seq.begin(), seq.end());
            seq.erase(unique(seq.begin(), seq.end()), seq.end());
            int las = -1;
            for(auto &it: seq) {
                int cur = it.second;
                if(las != -1) {
                    ++deg[cur];
                    edges[las].push_back(cur);
                }
                las = cur;
            }
        }
        for(int j = 0; j < m; ++j) {
            vector<pair<int, int> > seq;
            for(int i = 0; i < n; ++i)
                seq.push_back({mat[i][j], dsuFind(i * m + j)});
            sort(seq.begin(), seq.end());
            seq.erase(unique(seq.begin(), seq.end()), seq.end());
            int las = -1;
            for(auto &it: seq) {
                int cur = it.second;
                if(las != -1) {
                    ++deg[cur];
                    edges[las].push_back(cur);
                }
                las = cur;
            }
        }
        vector<int> rnk(tot);
        queue<int> que;
        for(int i = 0; i < tot; ++i)
            if(!deg[i]) {
                rnk[i] = 1;
                que.push(i);
            }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: edges[u])
                if(!(--deg[v])) {
                    rnk[v] = rnk[u] + 1;
                    que.push(v);
                }
        }
        vector<vector<int> > ret(n, vector<int>(m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                ret[i][j] = rnk[dsuFind(i * m + j)];
        return ret;
    }
};
