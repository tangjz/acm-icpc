class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = (int)jobs.size(), m = 1 << n;
        vector<int> w(m), lbt(m);
        for(int i = 1; i < m; ++i) {
            lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
            w[i] = w[i ^ (1 << lbt[i])] + jobs[lbt[i]];
        }
        vector<int> f(w.begin(), w.end());
        for(int t = 1; t < k; ++t) {
            vector<int> g(f.begin(), f.end());
            for(int i = 0; i < m; ++i)
                for(int j = i; j; j = (j - 1) & i)
                    g[i] = min(g[i], max(f[j], w[i ^ j]));
            f = move(g);
        }
        return f.back();
    }
};
