#include <cstdio>
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 1 << 19 | 1, mod = 998244353, seed = 1526;
int n, all, bit[maxn], a[maxn], b[maxn], ans;
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
int main() {
    while(scanf("%d", &n) == 1) {
        all = (1 << n) - 1;
        for(int i = 0; i <= all; ++i)
            scanf("%d", a + i);
        for(int i = 0; i <= all; ++i)
            scanf("%d", b + i);
        bit[0] = 1;
        for(int i = 1; i <= all; ++i) {
            bit[i] = bit[i >> 1] << (i & 1);
            a[i] = (LL)a[i] * bit[i] % mod;
        }
        ans = 0;
        for(int i = all; i >= 0; --i) {
            int msk = all ^ i, tim = 0;
            ULL cnt = 0;
            for(int j = msk; j; j = (j - 1) & msk) {
                cnt += (ULL)a[j] * b[i | j];
                (++tim) == 18 && (tim = 0, cnt %= mod);
            }
            cnt += (ULL)a[0] * b[i];
            cnt %= mod;
            ans = ((LL)seed * ans + cnt) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}