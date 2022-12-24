#include <cstdio>
typedef long long LL;
const int maxn = 19, maxd = 7, maxp = 10, mod = (int)1e9 + 7;
int f[maxn][maxd][maxd][3], len, num[maxn];
LL pw[maxn];
int solve(LL n) {
    for(len = 0; n; num[len++] = n % maxp, n /= maxp);
    int pj = 0, pk = 0, pv = 0, ret = 0;
    for(int i = len - 1; i >= 0; --i) {
        for(int x = 0; x < num[i]; ++x) {
            if(x == maxd)
                continue;
            int cj = (pj + x) % maxd, ck = (pk + pw[i] * x) % maxd, cv = (pv + pw[i] * x) % mod, cv2 = (LL)cv * cv % mod;
            for(int j = 0; j < maxd; ++j) {
                if((cj + j) % maxd == 0)
                    continue;
                for(int k = 0; k < maxd; ++k) {
                    if((ck + k) % maxd == 0)
                        continue;
                    ret = (ret + f[i][j][k][2] + (LL)(cv << 1) * f[i][j][k][1] + (LL)cv2 * f[i][j][k][0]) % mod;
                }
            }
        }
        if(num[i] == maxd)
            break;
        pj = (pj + num[i]) % maxd;
        pk = (pk + pw[i] * num[i]) % maxd;
        pv = (pv + pw[i] * num[i]) % mod;
    }
    return ret;
}
int main() {
    pw[0] = f[0][0][0][0] = 1;
    for(int i = 1; i < maxn; ++i) {
        pw[i] = (pw[i - 1] << 3) + (pw[i - 1] << 1);
        for(int j = 0; j < maxd; ++j)
            for(int k = 0; k < maxd; ++k)
                for(int x = 0; x < maxp; ++x) {
                    if(x == maxd)
                        continue;
                    int jj = (j + x) % maxd, kk = (k + pw[i - 1] * x) % maxd, v1 = pw[i - 1] * x % mod, v2 = (LL)v1 * v1 % mod;
                    (f[i][jj][kk][0] += f[i - 1][j][k][0]) >= mod && (f[i][jj][kk][0] -= mod);
                    f[i][jj][kk][1] = (f[i][jj][kk][1] + f[i - 1][j][k][1] + (LL)v1 * f[i - 1][j][k][0]) % mod;
                    f[i][jj][kk][2] = (f[i][jj][kk][2] + f[i - 1][j][k][2] + (LL)(v1 << 1) * f[i - 1][j][k][1] + (LL)v2 * f[i - 1][j][k][0]) % mod;
                }
    }
    int t;
    LL L, R;
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d%I64d", &L, &R);
        int ans = solve(R + 1) - solve(L);
        printf("%d\n", ans < 0 ? ans + mod : ans);
    }
    return 0;
}