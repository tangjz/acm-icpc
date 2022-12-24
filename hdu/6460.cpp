#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = (int)1e4 + 1, maxm = 1001, mod = (int)1e9 + 7;
int t, n, m, f[maxn][maxm], g[maxn][maxm];
int main() {
    scanf("%d", &t);
    for(int i = 0; i < maxm; ++i)
        f[0][i] = 1;
    g[0][0] = 1;
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            int a, b, *cf = f[i], *cg = g[i];
            memcpy(cf, f[i - 1], sizeof f[0]);
            memcpy(cg, g[i - 1], sizeof g[0]);
            scanf("%d%d", &a, &b);
            a = (a + 1) * b;
            for(int j = b; j < maxm; ++j) {
                j >= a && (cg[j] += cg[j - a]) >= mod && (cg[j] -= mod);
                (cf[j] += cf[j - b]) >= mod && (cf[j] -= mod);
            }
            for(int j = maxm - 1; j >= b; --j) {
                j >= a && (cf[j] -= cf[j - a]) < 0 && (cf[j] += mod);
                (cg[j] -= cg[j - b]) < 0 && (cg[j] += mod);
            }
        }
        printf("Case #%d:\n", Case);
        LL ans = 0;
        while(m--) {
            int L, R, v;
            scanf("%d%d%d", &L, &R, &v);
            L = (L + ans) % n + 1;
            R = (R + ans) % n + 1;
            if(L > R)
                swap(L, R);
            ans = 0;
            int *cf = f[R], *cg = g[L - 1];
            for(int i = 0; i <= v; ++i) {
                ans += (LL)cf[i] * cg[v - i];
                if(ans < 0)
                    ans = (ULL)ans % mod;
            }
            ans >= mod && (ans %= mod);
            printf("%d\n", (int)ans);
        }
    }
    return 0;
}