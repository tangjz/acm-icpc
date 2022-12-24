#include <cstdio>
#include <cstring>
const int maxn = 101, maxm = 1001;
int t, n, m, c[maxn], w[maxn], f[maxn][maxm], g[maxn][maxm];
bool p[maxn][maxm];
int main() {
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &m, &n);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", w + i, c + i);
        for(int i = 0; i <= m; ++i)
            f[n][i] = g[n][i] = 0;
        for(int i = n - 1; i >= 0; --i)
            for(int j = 0; j <= m; ++j) {
                f[i][j] = f[i + 1][j];
                g[i][j] = g[i + 1][j];
                p[i][j] = 0;
                if(j >= c[i]) {
                    int tf = f[i + 1][j - c[i]] + w[i], tg = g[i + 1][j - c[i]] + i + 1;
                    if(f[i][j] < tf || f[i][j] == tf && g[i][j] >= tg) {
                        f[i][j] = tf;
                        g[i][j] = tg;
                        p[i][j] = 1;
                    }
                }
            }
        int cc = 0;
        for(int i = 0, j = m, s = g[0][m]; i < n; ++i)
            if(p[i][j]) {
                j -= c[i];
                s -= i + 1;
                cc += c[i];
            }
        printf("Case #%d:\n%d %d\n", Case, f[0][m], cc);
        for(int i = 0, j = m, s = g[0][m]; i < n; ++i)
            if(p[i][j]) {
                j -= c[i];
                s -= i + 1;
                printf("%d%c", i + 1, " \n"[s == 0]);
            }
    }
    return 0;
}