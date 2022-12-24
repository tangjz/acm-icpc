#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 31;
int t, n[2], mod, c[maxn][maxn], pw2[maxn * maxn], prb[maxn][maxn], cur, pre = 1;
LL f[2][maxn][maxn][maxn];
inline void dp_clear(int step) {
    step &= 1;
    int lim0 = n[!step], lim1 = n[step];
    for(int i = 0; i <= lim0; ++i)
        for(int j = 1; j <= lim1; ++j)
            memset(f[cur][i][j] + 1, 0, j * sizeof(LL));
}
inline int mod_fix(LL &x) {
    return x < mod ? x : (x %= mod);
}
inline void mod_inc(LL &x, LL y) {
    (x += y) < 0 && (x = (ULL)x % mod);
}
inline int mod_inv(int x) {
    return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", n + 0, n + 1, &mod);
        for(int i = 0; i <= n[0] || i <= n[1]; ++i) {
            c[i][0] = c[i][i] = 1;
            for(int j = 1; j < i; ++j)
                (c[i][j] = c[i - 1][j] + c[i - 1][j - 1]) >= mod && (c[i][j] -= mod);
        }
        pw2[0] = 1;
        pw2[1] = (mod + 1) >> 1;
        for(int i = 1; i <= n[0] * n[1]; ++i)
            pw2[i] = (LL)pw2[i - 1] * pw2[1] % mod;
        for(int i = 0; i <= max(n[0], n[1]); ++i) {
            prb[i][0] = 1;
            (prb[i][1] = i ? prb[i - 1][1] << 1 | 1 : 0) >= mod && (prb[i][1] -= mod);
            for(int j = 2; j <= max(n[0], n[1]); ++j)
                prb[i][j] = (LL)prb[i][j - 1] * prb[i][1] % mod;
        }
        dp_clear(0);
        f[cur][0][1][1] = 1;
        LL ans = 0;
        for(int i = 1; i < min(n[0], n[1]) * 2; ++i) {
            swap(cur, pre);
            dp_clear(i);
            int lim0 = n[!(i & 1)], lim1 = n[i & 1];
            for(int j = 0; j < lim1; ++j)
                for(int k = 1; k <= lim0; ++k)
                    for(int x = 1; x <= k; ++x) {
                        if(!mod_fix(f[pre][j][k][x]))
                            continue;
                        int coeff = pw2[x * (lim1 - j)] * f[pre][j][k][x] % mod;
                        for(int y = 1, jj = j + 1; jj <= lim1; ++y, ++jj)
                            mod_inc(f[cur][k][jj][y], (LL)coeff * c[lim1 - j][y] % mod * prb[x][y]);
                    }
            if(i & 1)
                for(int j = 0; j <= lim0; ++j)
                    for(int k = 1; k <= lim1; ++k)
                        for(int x = 1; x <= k; ++x) {
                            if(!mod_fix(f[cur][j][k][x]))
                                continue;
                            mod_inc(ans, (LL)x * i * f[cur][j][k][x]);
                        }
        }
        ans = (LL)mod_fix(ans) * mod_inv(n[1]) % mod;
        printf("%d\n", mod_fix(ans));
    }
    return 0;
}