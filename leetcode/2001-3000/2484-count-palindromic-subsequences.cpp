class Solution {
public:
    int countPalindromes(string s) {
        typedef long long LL;
        const int maxd = 10, mod = (int)1e9 + 7;
        int n = s.size(), ans = 0;
        vector<int> a(maxd), b(maxd * maxd);
        vector<vector<int> > f(n, vector<int>(maxd)), g(n, vector<int>(maxd * maxd));
        for(int i = 0; i < n; ++i) {
            int o = s[i] - '0';
            for(int j = 0, u = o * maxd; j < maxd; ++j, ++u)
                (g[i][u] += f[i][j]) >= mod && (g[i][u] -= mod);
            (++f[i][o]) >= mod && (f[i][o] -= mod);
            if(i + 1 < n) {
                for(int j = 0; j < maxd; ++j)
                    f[i + 1][j] = f[i][j];
                for(int j = 0; j < maxd * maxd; ++j)
                    g[i + 1][j] = g[i][j];
            }
        }
        for(int i = n - 1; i >= 0; --i) {
            int o = s[i] - '0';
            if(i >= 2 && i + 2 < n)
                for(int j = 0; j < maxd * maxd; ++j)
                    ans = (ans + (LL)g[i - 1][j] * b[j]) % mod;
            for(int j = 0, u = o * maxd; j < maxd; ++j, ++u)
                (b[u] += a[j]) >= mod && (b[u] -= mod);
            (++a[o]) >= mod && (a[o] -= mod);
        }
        return ans;
    }
};
