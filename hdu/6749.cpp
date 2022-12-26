#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, maxd = 6, maxs = 1 << maxd | 1;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m, d;
        static int x[maxd + 1], y[maxd + 1], upp[maxs];
        scanf("%d%d%d", &n, &m, &d);
        int all = 1 << d;
        memset(upp, 0, all * sizeof(int));
        for(int i = 0; i < d; ++i) {
            int adt;
            scanf("%d%d%d", x + i, y + i, &adt);
            for(int j = 0; j < all; ++j)
                if((j >> i) & 1)
                    upp[j] += adt;
        }
        if(upp[all - 1] < n * m) {
            puts("-1");
            continue;
        }
        int L = 0, R = n + m;
        while(L < R) {
            int M = (L + R) >> 1;
            bool chk = 1;
            static int low[maxs];
            memset(low, 0, all * sizeof(int));
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= m; ++j) {
                    int msk = 0;
                    for(int k = 0; k < d; ++k)
                        if(abs(i - x[k]) + abs(j - y[k]) <= M)
                            msk |= 1 << k;
                    ++low[msk];
                }
            for(int i = 1; i < all; i <<= 1)
                for(int j = 0; j < all; ++j)
                    if(i & j)
                        low[j] += low[i ^ j];
            for(int i = 0; chk && i < all; ++i)
                chk &= low[i] <= upp[i];
            if(chk) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        printf("%d\n", L);
    }
    return 0;
}
