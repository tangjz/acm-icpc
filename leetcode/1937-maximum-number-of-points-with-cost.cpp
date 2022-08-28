class Solution {
public:
    long long maxPoints(vector<vector<int>>& mat) {
        typedef long long LL;
        const LL INF = (LL)1e11;
        int n = mat.size(), m = mat[0].size();
        vector<LL> f(m);
        for(int i = 0; i < m; ++i) {
            f[i] = mat[0][i];
        }
        for(int i = 1; i < n; ++i) {
            vector<LL> g(m, -INF);
            LL pre = -INF, suf = -INF;
            for(int j = 0; j < m; ++j) {
                pre = max(pre - 1, f[j]);
                g[j] = max(g[j], pre + mat[i][j]);
            }
            for(int j = m - 1; j >= 0; --j) {
                suf = max(suf - 1, f[j]);
                g[j] = max(g[j], suf + mat[i][j]);
            }
            f = move(g);
        }
        return *max_element(f.begin(), f.end());
    }
};
