#include <cstdio>
#include <algorithm>
const int maxn = 60001, maxk = 21, INF = 0x3f3f3f3f;
int t, n, m, a[maxn], b[maxn], c[maxn << 1 | 1], p[maxn], tot, que[maxk];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", b + i);
            p[b[i]] = i;
        }
        for(int i = 0; i <= n; ++i)
            c[n - i] = i;
        for(int i = 1; i <= n; ++i)
            c[i + n] = 0;
        for(int i = 1; i <= n; ++i) {
            tot = 0;
            for(int j = std::max(a[i] - m, 1), jLim = std::min(a[i] + m, n); j <= jLim; ++j)
                que[tot++] = p[j];
            std::sort(que, que + tot);
            for(int j = 0; j < tot; ++j) {
                int x = i, y = que[j], v = std::min(c[x - 1 + n - y] + x - 1, c[x + n - y + 1] + x) + 1;
                c[x + n - y] = v - x;
            }
        }
        printf("%d\n", c[n] + n);
    }
    return 0;
}
