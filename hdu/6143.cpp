#include <cstdio>
typedef long long LL;
const int maxn = 2001, mod = (int)1e9 + 7;
int c[maxn][maxn], t, n, m, f[maxn];
int main() {
    for(int i = 0; i < maxn; ++i) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j)
            (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i) {
            f[i] = 1;
            for(int j = 1; j <= n; ++j)
                f[i] = (LL)f[i] * i % mod;
        }
        for(int i = m; i >= 0; --i) {
            int tmp = 0;
            for(int j = 0; j <= i; ++j)
                tmp = (tmp + ((i - j) & 1 ? -1LL : 1LL) * c[i][j] * f[j]) % mod;
            tmp < 0 && (tmp += mod);
            f[i] = tmp;
        }
        int ans = 0;
        for(int i = 1; i <= m; ++i)
            for(int j = 1; i + j <= m; ++j)
                ans = (ans + (LL)c[m][i] * c[m - i][j] % mod * f[i] % mod * f[j]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
