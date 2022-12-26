#include <bits/stdc++.h>
const int mod = (int)1e9 + 7, maxd = 30, maxm = 8, half = maxm >> 1, quat = half >> 1;
typedef int Matrix[maxm | 1][maxm | 1];
void matMul(Matrix a, Matrix b, Matrix &c) {
    typedef long long LL;
    static LL tmp[maxm | 1][maxm | 1];
    for(int i = 0; i < maxm; ++i)
        for(int j = 0; j < maxm; ++j)
            tmp[i][j] = 0;
    for(int i = 0; i < maxm; ++i)
        for(int j = 0; j < maxm; ++j) {
            if(!a[i][j])
                continue;
            for(int k = 0; k < maxm; ++k) {
                if(!b[j][k])
                    continue;
                tmp[i][k] += (LL)a[i][j] * b[j][k];
            }
        }
    for(int i = 0; i < maxm; ++i)
        for(int j = 0; j < maxm; ++j)
            c[i][j] = tmp[i][j] < mod ? tmp[i][j] : tmp[i][j] % mod;
}
void matPow(Matrix &mat, int exp) {
    static Matrix tmp;
    for(int i = 0; i < maxm; ++i)
        for(int j = 0; j < maxm; ++j) {
            tmp[i][j] = mat[i][j];
            mat[i][j] = i == j;
        }
    for( ; exp > 0; exp >>= 1, matMul(tmp, tmp, tmp))
        if(exp & 1)
            matMul(mat, tmp, mat);
}
int t, n, L, R, q;
Matrix f[maxd];
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d%d", &n, &L, &R, &q);
        int mx = 0;
        for( ; 1 << mx <= R; ++mx);
        for(int i = 0; i < mx; ++i) {
            Matrix &mat = f[i];
            for(int j = 0; j < maxm; ++j)
                for(int k = 0; k < maxm; ++k)
                    mat[j][k] = 0;
            int mask = 1 << i, curR = (R & mask) > 0, lowR = R & (mask - 1);
            for(int i = 0; i < half; ++i)
                mod_inc(mat[i][i ^ curR], lowR + 1);
            if(curR)
                for(int i = 0; i < half; ++i)
                    mod_inc(mat[i][quat | i], i & quat ? mask : 1);
            if(L) {
                int curL = ((L - 1) & mask) > 0, lowL = (L - 1) & (mask - 1);
                for(int i = 0; i < half; ++i)
                    mod_inc(mat[i][half | (i ^ curL)], mod - (lowL + 1));
                if(curL)
                    for(int i = 0; i < half; ++i)
                        mod_inc(mat[i][half | quat | i], mod - (i & quat ? mask : 1));
            }
            for(int i = half; i < maxm; ++i)
                for(int j = 0; j < maxm; ++j)
                    mat[i][j] = mat[i ^ half][j ^ half];
            matPow(mat, n);
        }
        while(q--) {
            int K;
            scanf("%d", &K);
            if(K >= (1 << mx)) {
                puts("0");
                continue;
            }
            if(!R) {
                puts("1");
                continue;
            }
            int ans = 0;
            bool even = 1, odd = 1;
            for(int i = mx - 1; i >= 0 && (even || odd); --i) {
                Matrix &mat = f[i];
                int curL = L && (((L - 1) >> i) & 1), curR = (R >> i) & 1, curK = (K >> i) & 1;
                if(even)
                    mod_inc(ans, mat[0][quat | curK]);
                if(odd)
                    mod_inc(ans, mat[0][half | quat | curK]);
                int emsk = n & 1 ? curR : 0, omsk = emsk ^ curL ^ curR;
                even &= emsk == curK;
                odd &= omsk == curK;
            }
            Matrix &mat = f[0];
            int curK = K & 1;
            if(even)
                mod_inc(ans, mat[0][curK]);
            if(odd)
                mod_inc(ans, mat[0][half | curK]);
            printf("%d\n", ans);
        }
    }
    return 0;
}
