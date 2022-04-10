#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = 5, maxd = 31, maxs = 1 << 8 | 1, mod = (int)1e9 + 9;

struct Matrix {
    int r, c, data[maxs][maxs];
    void reset(int _r, int _c) {
        r = _r;
        c = _c;
        for(int i = 0; i < r; ++i)
            memset(data, 0, c * sizeof(int));
    }
    void assignMul(Matrix const &lft, Matrix const &rht) {
        static i64 tmp[maxs][maxs];
        r = lft.r;
        c = rht.c;
        for(int i = 0; i < r; ++i)
            memset(tmp[i], 0, c * sizeof(i64));
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < lft.c; ++j) {
                if(!lft.data[i][j])
                    continue;
                for(int k = 0; k < c; ++k) {
                    if(!rht.data[j][k])
                        continue;
                    i64 &dst = tmp[i][k], prd = (i64)lft.data[i][j] * rht.data[j][k];
                    if(dst + prd < 0)
                        dst %= mod;
                    dst += prd;
                }
            }
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                data[i][j] = tmp[i][j] < mod ? tmp[i][j] : tmp[i][j] % mod;
    }
} tr[maxn][maxd], vec;

int mx[maxn];

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    int all = 1 << (n + n);
    vec.reset(1, all);
    ++vec.data[0][0];
    for(int i = 0; m > 0; ++i, m >>= 1) {
        if(!(m & 1))
            continue;
        for( ; mx[n] < i; ++mx[n])
            tr[n][mx[n] + 1].assignMul(tr[n][mx[n]], tr[n][mx[n]]);
        vec.assignMul(vec, tr[n][i]);
    }
    int ans = 0;
    for(int i = 0; i < all; ++i)
        (ans += vec.data[0][i]) >= mod && (ans -= mod);
    printf("%d\n", ans);
}

int main() {
    static int dx[4] = {-1, -1, -2, -2}, dy[4] = {-2, 2, -1, 1};
    for(int n = 1; n <= 4; ++n) {
        int all = 1 << (n + n);
        tr[n][0].reset(all, all);
        for(int msk = 0; msk < (all << n); ++msk) {
            bool ban = 0;
            for(int x = 0, rem = msk; !ban && x < 3; ++x)
                for(int y = 0; !ban && y < n; ++y, rem >>= 1) {
                    if(!(rem & 1))
                        continue;
                    for(int o = 0; !ban && o < 4; ++o) {
                        int xx = x + dx[o], yy = y + dy[o];
                        if(xx < 0 || yy < 0 || yy >= n)
                            continue;
                        int idx = xx * n + yy;
                        ban |= (msk >> idx) & 1;
                    }
                }
            if(ban)
                continue;
            int u = msk & (all - 1), v = (msk >> n) & (all - 1);
            ++tr[n][0].data[u][v];
        }
        mx[n] = 0;
    }

    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}