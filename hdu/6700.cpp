#include <bits/stdc++.h>
using namespace std;
const int maxn = 35;
typedef long long LL;
typedef unsigned long long ULL;
typedef int Matrix[maxn][maxn];
int t, n, mod, cur, pre = 1, f[2][maxn + 2], deg[2];
LL m;
Matrix mat[2];
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
inline int mod_fix(LL &x) {
    return x < mod ? x : (x %= mod);
}
inline void mod_inc_mul(LL &x, int y, int z) {
    y && z && (x += (LL)y * z) < 0 && (x = (ULL)x % mod);
}
inline int mod_inv(int x) {
    int y = mod, u = 1, v = 0;
    while(x) {
        int q = y / x;
        swap(x, y);
        x -= q * y;
        swap(u, v);
        u -= q * v;
    }
    return v < 0 ? v + mod : v;
}
LL g[maxn][maxn];
inline int mat_det() {
    int det = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(!mod_fix(g[j][i]))
                continue;
            if(i == j)
                break;
            if(det)
                det = mod - det;
            for(int k = i; k < n; ++k)
                swap(g[i][k], g[j][k]);
        }
        if(!g[i][i])
            return 0;
        det = det * g[i][i] % mod;
        for(int j = i, k = mod_inv(g[i][i]); j < n; ++j)
            g[i][j] = (LL)mod_fix(g[i][j]) * k % mod;
        for(int j = i + 1; j < n; ++j) {
            if(!mod_fix(g[j][i]))
                continue;
            int d = mod - g[j][i];
            for(int k = i; k < n; ++k)
                mod_inc_mul(g[j][k], d, g[i][k]);
        }
    }
    return det;
}
LL vec[maxn << 1 | 1];
inline void poly_mod() {
    for(int i = deg[0] - deg[1]; i >= 0; --i) {
        if(!mod_fix(vec[i + deg[1]]))
            continue;
        int d = mod - vec[i + deg[1]];
        for(int j = 0; j <= deg[1]; ++j)
            mod_inc_mul(vec[i + j], d, f[1][j]);
    }
    for( ; deg[0] && !mod_fix(vec[deg[0]]); --deg[0]);
    for(int i = 0; i <= deg[0]; ++i)
        f[0][i] = mod_fix(vec[i]);
}
inline void mat_next() {
    swap(cur, pre);
    Matrix &F = mat[cur], &G = mat[pre];
    for(int i = 0; i < n; ++i)
        for(int j = 1; j < n; ++j) {
            mod_inc(F[i][j], G[i][j - 1]);
            mod_inc(F[i][j - 1], G[i][j]);
        }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%lld%d", &n, &m, &mod);
        if((n & 1) && (m & 1)) {
            puts("0");
            continue;
        }
        if(n > m) {
            int t = m;
            m = n;
            n = t;
        }
        if(n == 1) {
            puts("1");
            continue;
        }
        f[cur][0] = 1;
        for(int i = 1; i <= n; ++i) {
            swap(cur, pre);
            f[cur][i] = f[pre][i - 1];
            for(int j = i - 1; j > 0; --j) {
                f[cur][j] = f[pre][j - 1];
                mod_inc(f[cur][j], mod - f[pre][j]);
                mod_inc(f[cur][j], mod - f[cur][j - 1]);
            }
            f[cur][0] = mod - f[pre][0];
        }
        deg[1] = n;
        if(!cur)
            memcpy(f[1], f[cur], (deg[1] + 1) * sizeof(int));
        deg[0] = 0;
        f[0][0] = 1;
        int mx = 0;
        for( ; (1LL << mx) <= (m >> 1); ++mx);
        for(int i = mx - 1; i >= 0; --i) {
            memset(vec, 0, (deg[0] << 1 | 1) * sizeof(LL));
            for(int j = 0; j <= deg[0]; ++j)
                for(int k = 0; k <= deg[0]; ++k)
                    mod_inc_mul(vec[j + k], f[0][j], f[0][k]);
            deg[0] <<= 1;
            poly_mod();
            if((m >> (i + 1)) & 1) {
                vec[0] = 0;
                for(int j = 0; j <= deg[0]; ++j)
                    vec[j + 1] = f[0][j];
                ++deg[0];
                poly_mod();
            }
        }
        for(int i = 0; i < n; ++i) {
            memset(mat[0][i], 0, n * sizeof(int));
            memset(mat[1][i], 0, n * sizeof(int));
            memset(g[i], 0, n * sizeof(LL));
        }
        for(int i = 0; i <= deg[0]; ++i) {
            if(i) {
                mat_next();
                mat_next();
            } else {
                for(int j = 0; j < n; ++j)
                    mat[cur][j][j] = 1;
                if(m & 1)
                    mat_next();
            }
            if(f[0][i])
                for(int j = 0; j < n; ++j)
                    for(int k = 0; k < n; ++k)
                        mod_inc_mul(g[j][k], f[0][i], mat[cur][j][k]);
        }
        int o = !(m & 1);
        for(int i = 0; i + i + o < n; ++i) {
            for(int j = 0; j + j + 1 < n; ++j)
                g[i][j] = g[i << 1 | o][j << 1 | 1];
        }
        n >>= 1;
        printf("%d\n", mat_det());
    }
    return 0;
}