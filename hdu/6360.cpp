#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 60, maxd = 4, len[maxd + 1] = {1, 2, 3, 5}, coeff[maxd + 1] = {1, 15, 20, 24}, BLEN = 18, BMSK = (1 << 18) - 1;
int t, n, m, a[maxn + 1], sum[maxd + 1];
LL c[maxn + 1][maxn + 1], f[maxn + 1];
inline LL mod_mul(LL x, LL y, LL m) {
    LL yH = y >> BLEN, yL = y & BMSK;
    LL ret = yH ? ((x * yH % m) << BLEN) % m : 0;
    return (ret + x * yL) % m;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        if(m == 1) {
            for(int i = 0; i < n; ++i)
                scanf("%*d");
            puts("0");
            continue;
        }
        memset(sum, 0, sizeof sum);
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            for(int j = 0; j < maxd; ++j)
                sum[j] += a[i] ? (a[i] - 1) / len[j] + 1 : 0;
        }
        LL ans = 0, mod = (LL)maxn * m;
        for(int i = 0; i <= maxn; ++i) {
            c[i][0] = c[i][i] = 1;
            for(int j = 1; j < i; ++j)
                (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
        }
        for(int i = 0; i < maxd; ++i) {
            int upp = maxn / len[i];
            if(sum[i] > upp)
                continue;
            memset(f, 0, sizeof f);
            f[0] = 1;
            for(int j = 0; j < n; ++j) {
                int low = a[j] ? (a[j] - 1) / len[i] + 1 : 0;
                for(int x = upp; x >= 0; --x) {
                    LL res = 0;
                    for(int y = low; y <= upp; ++y)
                        (res += mod_mul(c[x][y], f[x - y], mod)) >= mod && (res -= mod);
                    f[x] = res;
                }
            }
            ans = (ans + coeff[i] * f[upp]) % mod;
        }
        assert(ans % maxn == 0);
        printf("%d\n", (int)(ans / maxn));
    }
    return 0;
}
