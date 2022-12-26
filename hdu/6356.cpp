#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 17;
int t, n, m, mx, Log[maxn], a[maxd][maxn];
unsigned int X, Y, Z;
unsigned int rng61() {
    X ^= X << 11;
    X ^= X >> 4;
    X ^= X << 5;
    X ^= X >> 14;
    unsigned int tmp = X ^ Y ^ Z;
    X = Y;
    Y = Z;
    Z = tmp;
    return Z;
}
inline void upd(int &x, int y) {
    x < y && (x = y);
}
int main() {
    for(int i = 2; i < maxn; ++i)
        Log[i] = Log[i >> 1] + 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%u%u%u", &n, &m, &X, &Y, &Z);
        for(mx = 0; 1 << mx <= n; ++mx);
        while(m--) {
            int L = rng61() % n + 1, R = rng61() % n + 1, v = rng61() & ((1 << 30) - 1);
            if(L > R)
                swap(L, R);
            int d = Log[R - L + 1];
            upd(a[d][L], v);
            upd(a[d][R - (1 << d) + 1], v);
        }
        for(int i = mx - 1; i > 0; --i)
            for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
                upd(a[i - 1][j], a[i][j]);
                upd(a[i - 1][j + (1 << (i - 1))], a[i][j]);
                a[i][j] = 0;
            }
        LL ans = 0;
        for(int i = 1; i <= n; ++i) {
            ans ^= (LL)i * a[0][i];
            a[0][i] = 0;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
