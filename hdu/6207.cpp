#include <cstdio>
const int maxn = 801;
typedef double DB;
int t, n, st, mod, vf[maxn][maxn], vg[maxn][maxn], vh[maxn][maxn];
DB f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], out[maxn];
inline int mod_add(int x, int y) {
    for(x += y; x >= mod; x -= mod);
    for( ; x < 0; x += mod);
    return x;
}
inline int mod_sub(int x, int y) {
    for(x -= y; x < 0; x += mod);
    for( ; x >= mod; x -= mod);
    return x;
}
DB F(int, int);
DB G(int, int);
DB H(int, int);
DB F(int L, int R) {
    while(L >= (n << 1)) {
        L -= n << 1;
        R = mod_sub(R, n << 1);
    }
    if(vf[L][R] == st)
        return f[L][R];
    vf[L][R] = st;
    DB &ret = f[L][R];
    int len = mod_sub(R + 1, L);
    if(len <= 2)
        return ret = 1;
    ret = 0;
    int qL = L, qR = L <= R ? R : R + mod;
    while(qL <= qR) {
        int M1 = qL - qL % (n << 1) + 1, M2 = qL - qL % (n << 1) + (n << 1) - 1;
        M1 < qL && (M1 += n << 1);
        M2 < qL && (M2 += n << 1);
        if(M1 < M2) {
            if(M1 <= qR) { // [qL, M1-1] : -2, +2 [M1] : -1, +2
                ret += L < M1 - 3 ? G(L, mod_sub(M1, 4)) : 0;
                ret -= L < qL - 3 ? G(L, mod_sub(qL, 4)) : 0;
                ret += L < M1 - 1 ? F(L, mod_sub(M1, 2)) : 0;
                ret += qL + 2 < qR ? H(mod_add(qL, 3), R) : 0;
                ret -= M1 + 2 < qR ? H(mod_add(M1, 3), R) : 0;
                ret += M1 + 2 < qR ? F(mod_add(M1, 3), R) : 0;
                qL = M1 + 1;
            } else { // [qL, qR] : -2, +2
                ret += L < qR - 2 ? G(L, mod_sub(qR, 3)) : 0;
                ret -= L < qL - 3 ? G(L, mod_sub(qL, 4)) : 0;
                ret += qL + 2 < qR ? H(mod_add(qL, 3), R) : 0;
                ret -= qR + 3 < qR ? H(mod_add(qL, 4), R) : 0;
                qL = qR + 1;
            }
        } else {
            if(M2 <= qR) { // [qL, M2-1] : -2, +2 [M2] : -2, +1
                ret += L < M2 - 3 ? G(L, mod_sub(M2, 4)) : 0;
                ret -= L < qL - 3 ? G(L, mod_sub(qL, 4)) : 0;
                ret += L < M2 - 2 ? F(L, mod_sub(M2, 3)) : 0;
                ret += qL + 2 < qR ? H(mod_add(qL, 3), R) : 0;
                ret -= M2 + 2 < qR ? H(mod_add(M2, 3), R) : 0;
                ret += M2 + 1 < qR ? F(mod_add(M2, 2), R) : 0;
                qL = M2 + 1;
            } else { // [qL, qR] : -2, +2
                ret += L < qR - 2 ? G(L, mod_sub(qR, 3)) : 0;
                ret -= L < qL - 3 ? G(L, mod_sub(qL, 4)) : 0;
                ret += qL + 2 < qR ? H(mod_add(qL, 3), R) : 0;
                ret -= qR + 3 < qR ? H(mod_add(qL, 4), R) : 0;
                qL = qR + 1;
            }
        }
    }
    return ret = ret / len + 1;
}
DB G(int L, int R) {
    if(vg[L][R] == st)
        return g[L][R];
    vg[L][R] = st;
    return g[L][R] = (L != R ? G(L, mod_sub(R, 1)) : 0) + F(L, R);
}
DB H(int L, int R) {
    if(vh[L][R] == st)
        return h[L][R];
    vh[L][R] = st;
    return h[L][R] = F(L, R) + (L != R ? H(mod_add(L, 1), R) : 0);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        ++st;
        scanf("%d", &n);
        mod = n << 3;
        DB ans = 0;
        for(int i = 0; i <= n; ++i) {
            int pL = mod_add(i, 3), pR = mod_sub(i, 3);
            if(i == 1)
                pR = mod_add(pR, 1);
            out[i] = F(pL, pR);
            ans += i && i < n ? out[i] : out[i] / 2;
        }
        for(int i = n + 1; i < n << 1; ++i)
            out[i] = out[(n << 1) - i];
        for(int i = n << 1; i < n << 3; ++i)
            out[i] = out[i - (n << 1)];
        printf("%.6f\n", ans / n + 1);
        for(int i = 0; i < n << 3; ++i)
            printf("%.6f ", out[i] + 1);
        puts("");
    }
    return 0;
}