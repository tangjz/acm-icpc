class Solution {
public:
    int stringCount(int n) {
        typedef long long LL;
        static const int maxv = (int)1e5 + 27, maxd = 26, mod = (int)1e9 + 7;
        static int f[4][maxv] = {};
        if(!f[0][0]) {
            for(int i = 0; i < 4; ++i) {
                f[i][0] = 1;
                f[i][1] = maxd - i;
                for(int j = 2; j < maxv; ++j)
                    f[i][j] = (LL)f[i][j - 1] * f[i][1] % mod;
            }
        }
        static const int coe[2][4] = {{1, mod-3, 3, mod-1}, {0, mod-1, 2, mod-1}};
        int ans = 0;
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 4; ++j)
                ans = (ans + (i ? (LL)n * f[j][n - 1] % mod : (LL)f[j][n]) * coe[i][j]) % mod;
        return ans;
        // 26^n - 3 25^n - n 25^(n-1) + 3 24^n + 2 n 24^(n-1) - 23^n - n 22^(n-1)
    }
};
