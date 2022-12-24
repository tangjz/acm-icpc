#include <cstdio>
typedef long long LL;
const int maxn = 100001, maxm = 4, mod = 998244353;
int f[maxm | 1][maxn], g[2][maxm | 1][maxn], cur, pre = 1;
void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
int main() {
    int t, n, sqn;
    for(sqn = 1; sqn * sqn < maxn << 1; ++sqn);
    f[0][0] = g[cur][0][0] = 1;
    for(int i = 1; i * sqn < maxn; ++i) {
        pre ^= 1;
        cur ^= 1;
        for(int j = 0; j < maxm; ++j)
            for(int k = 0; k < maxn; ++k) {
                g[cur][j][k] = 0;
                if(k >= i)
                    mod_inc(g[cur][j][k], g[cur][j][k - i]);
                if(k >= sqn) {
                    mod_inc(g[cur][j][k], g[pre][j][k - sqn]);
                    if(j)
                        mod_inc(g[cur][j][k], g[pre][j - 1][k - sqn]);
                }
                mod_inc(f[j][k], g[cur][j][k]);
            }
    }
    for(int i = 1; i < sqn; ++i)
        for(int j = 0; j < maxm; ++j)
            for(int k = i; k < maxn; ++k) {
                mod_inc(f[j][k], f[j][k - i]);
                if(j)
                    mod_inc(f[j][k], f[j - 1][k - i]);
            }
    for(int i = 1; i < maxn; ++i)
        f[0][i] = (f[1][i] + 6LL * (f[2][i] + f[3][i])) % mod;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("%d\n", f[0][n]);
    }
    return 0;
}