class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int> > e(n);
        vector<int> seq, in(n), out(n), par(n, -1), ctr(n + 1);
        for(auto &it: edges) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        seq.reserve(n);
        function<void(int)> dfs = [&](int u) {
            seq.push_back(u);
            in[u] = seq.size() - 1;
            for(int v: e[u]) {
                if(v == par[u])
                    continue;
                par[v] = u;
                dfs(v);
            }
            out[u] = seq.size() - 1;
        };
        dfs(0);
        for(auto &it: guesses) {
            int u = it[0], v = it[1], w = -1;
            if(par[u] == v) {
                swap(u, v);
                w = -w;
            }
            if(w > 0) {
                ++ctr[in[v]];
                --ctr[out[v] + 1];
            } else {
                ++ctr[0];
                --ctr[in[v]];
                ++ctr[out[v] + 1];
                --ctr[n];
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += ctr[i] >= k;
            ctr[i + 1] += ctr[i];
        }
        return ans;
    }
};
