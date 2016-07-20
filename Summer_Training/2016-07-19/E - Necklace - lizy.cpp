#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

int n, m, x, y, c[512];
bool g[19][19];
int f[512][512][19][2];

int main() {
    for (int i = 0; i < 512; ++i) c[i] = __builtin_popcount(i);

    while (scanf("%d%d", &n, &m) == 2) {
        memset(g, 0, sizeof g);
        while (m--) {
            scanf("%d%d", &x, &y);
            g[--x][--y] = true;
        }
        if (n == 0) {
            puts("0");
            continue;
        }
        int o = 1 << n;
        memset(f, 63, sizeof f);
        f[0][1][0][0] = 0;
        for (int s = 0; s < o; ++s) for (int t = 0; t < o; ++t) {
            if (c[s] == c[t]) {
                for (int j = 0; j < n; ++j) {
                    if (!(s & 1 << j)) continue;
                    for (int k = 0; k < n; ++k) {
                        if (t & 1 << k) continue;
                        if (g[j][k]) {
                            f[s][t | 1 << k][k][1] = min(f[s][t | 1 << k][k][1], f[s][t][j][1]);
                            f[s][t | 1 << k][k][1] = min(f[s][t | 1 << k][k][1], f[s][t][j][0] + 1);
                        } else {
                            f[s][t | 1 << k][k][1] = min(f[s][t | 1 << k][k][1], f[s][t][j][1]);
                            f[s][t | 1 << k][k][0] = min(f[s][t | 1 << k][k][0], f[s][t][j][0]);
                        }

                    }
                }
            } else if (c[t] == c[s] + 1) {
                for (int j = 0; j < n; ++j) {
                    if (!(t & 1 << j)) continue;
                    for (int k = 0; k < n; ++k) {
                        if (s & 1 << k) continue;
                        if (g[k][j]) {
                            f[s | 1 << k][t][k][1] = min(f[s | 1 << k][t][k][1], f[s][t][j][0] + 1);
                            f[s | 1 << k][t][k][1] = min(f[s | 1 << k][t][k][1], f[s][t][j][1] + 1);
                        } else {
                            f[s | 1 << k][t][k][0] = min(f[s | 1 << k][t][k][0], f[s][t][j][0]);
                            f[s | 1 << k][t][k][0] = min(f[s | 1 << k][t][k][0], f[s][t][j][1]);
                        }

                    }
                }
            }
        }
        int ans = 0x3fffffff;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, f[o - 1][o - 1][i][0] + g[i][0]);
            ans = min(ans, f[o - 1][o - 1][i][1]);
        }
        printf("%d\n", ans);
    }

    return 0;
}
