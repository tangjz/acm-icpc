class Solution {
public:
    int maximumRows(vector<vector<int>>& mat, int cols) {
        int n = mat.size(), m = mat[0].size();
        vector<int> f(1 << m), g(1 << m);
        for(int i = 0; i < n; ++i) {
            int msk = 0;
            for(int j = 0; j < m; ++j)
                msk = msk << 1 | mat[i][m - 1 - j];
            ++g[msk];
        }
        for(int i = 1; i < (1 << m); i <<= 1)
            for(int j = 0; j < (1 << m); ++j)
                if(i & j)
                    g[j] += g[j ^ i];
        int ans = 0;
        for(int i = 1; i < (1 << m); ++i) {
            f[i] = f[i >> 1] + (i & 1);
            if(f[i] == cols)
                ans = max(ans, g[i]);
        }
        return ans;
    }
};
