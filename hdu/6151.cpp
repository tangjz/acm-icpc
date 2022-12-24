#include <cstdio>
#include <cstring>
const int maxn = 21, maxs = 1 << 20 | 1;
int t, n, m, q, a[maxn], b[maxn], bits[maxs], ex[maxs], ey[maxs];
int solve(int S, int T, int e[maxs]) {
    int ways = 1;
    static bool f[maxs];
    for(int i = S; i; i = (i - 1) & S)
        f[i] = bits[e[i] & T] >= bits[i];
    for(int i = 1; i <= S; i <<= 1)
        if(S & i)
            for(int msk = S ^ i, j = msk; j; j = (j - 1) & msk)
                f[j | i] &= f[j];
    for(int i = S; i; i = (i - 1) & S)
        ways += f[i];
    return ways;
}
int main() {
    for(int i = 1; i < maxs; ++i)
        bits[i] = bits[i >> 1] + (i & 1);
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d%d", &n, &m, &q);
        memset(ex, 0, (1 << n) * sizeof(int));
        memset(ey, 0, (1 << m) * sizeof(int));
        for(int i = 0; i < n; ++i)
            for(int j = 0, o; j < m; ++j) {
                scanf("%1d", &o);
                ex[1 << i] |= o << j;
                ey[1 << j] |= o << i;
            }
        for(int i = 0; i < 1 << n; ++i) {
            int j = i & -i;
            if(j < i)
                ex[i] = ex[j] | ex[i ^ j];
        }
        for(int i = 0; i < 1 << m; ++i) {
            int j = i & -i;
            if(j < i)
                ey[i] = ey[j] | ey[i ^ j];
        }
        for(int i = 0; i < n; ++i)
            scanf("%d", a + i);
        for(int i = 0; i < m; ++i)
            scanf("%d", b + i);
        printf("Case #%d:", Case);
        while(q--) {
            int r, mskx = 0, msky = 0;
            scanf("%d", &r);
            for(int i = 0; i < n; ++i)
                mskx |= (a[i] % r == 0) << i;
            for(int i = 0; i < m; ++i)
                msky |= (b[i] % r == 0) << i;
            printf(" %I64d", (long long)solve(mskx, msky, ex) * solve(msky, mskx, ey) - 1);
        }
        putchar('\n');
    }
    return 0;
}