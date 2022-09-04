class Solution {
public:
    int colorTheGrid(int m, int n) {
        vector<vector<int> > seq, nxt;
        for(int i = 0; i < 3; ++i)
            seq.push_back({i});
        for(int i = 1; i < m; ++i) {
            nxt.clear();
            for(auto &vec: seq)
                for(int j = 0; j < 3; ++j)
                    if(vec.back() != j) {
                        nxt.push_back(vec);
                        nxt.back().push_back(j);
                    }
            seq.swap(nxt);
        }
        int tot = seq.size();
        vector<vector<int> > e(tot);
        for(int i = 0; i < tot; ++i)
            for(int j = 0; j < tot; ++j) {
                bool skp = 0;
                for(int k = 0; !skp && k < m; ++k)
                    skp |= seq[i][k] == seq[j][k];
                if(!skp)
                    e[i].push_back(j);
            }
        const int mod = (int)1e9 + 7;
        vector<int> f(tot, 1), g;
        for(int i = 1; i < n; ++i) {
            g.assign(tot, 0);
            for(int u = 0; u < tot; ++u) {
                if(!f[u])
                    continue;
                for(int v: e[u])
                    (g[v] += f[u]) >= mod && (g[v] -= mod);
            }
            f.swap(g);
        }
        int ans = 0;
        for(int i = 0; i < tot; ++i)
            (ans += f[i]) >= mod && (ans -= mod);
        return ans;
    }
};
