#include <cstdio>
#include <algorithm>
const int maxn = 10000001, maxm = 101;
int n, m, b[maxm], ord[maxm];
unsigned x, y, z, t, a[maxn], ans[maxm];
int main() {
    for(int Case = 1; scanf("%d%d%u%u%u", &n, &m, &x, &y, &z) == 5; ++Case) {
        for(int i = 0; i < n; ++i) {
            x ^= x << 16;
            x ^= x >> 5;
            x ^= x << 1;
            t = x;
            x = y;
            y = z;
            a[i] = z = t ^ x ^ y;
        }
        for(int i = 0; i < m; ++i) {
            scanf("%d", b + i);
            ord[i] = i;
        }
        std::sort(ord, ord + m, [&](int const &u, int const &v) {
            return b[u] > b[v];
        });
        for(int i = 0, j = n; i < m; ++i) {
            int o = ord[i];
            if(b[o] < j) {
                std::nth_element(a, a + b[o], a + j);
                j = b[o];
            }
            ans[o] = a[b[o]];
        }
        printf("Case #%d: ", Case);
        for(int i = 0; i < m; ++i)
            printf("%u%c", ans[i], " \n"[i == m - 1]);
    }
    return 0;
}
