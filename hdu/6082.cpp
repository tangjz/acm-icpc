#include <cstdio>
#include <cstring>
const int maxn = 100001, maxm = 1001, maxb = 11, INF = 0x3f3f3f3f;
int n, m, a[maxn], b[maxn], c[maxm], w[maxm], sz[maxb], f[maxb][maxm];
int main() {
    while(scanf("%d%d", &n, &m) == 2) {
        memset(sz, 0, sizeof sz);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", a + i, b + i);
            if(sz[b[i]] < a[i])
                sz[b[i]] = a[i];
        }
        for(int i = 0; i < m; ++i)
            scanf("%d%d", w + i, c + i);
        for(int i = 0; i < maxb; ++i) {
            if(!sz[i])
                continue;
            int *ff = f[i], upp = sz[i];
            memset(ff + 1, 0x3f, sz[i] * sizeof(int));
            for(int j = 0; j < m; ++j) {
                if(c[j] <= i)
                    continue;
                int cc = c[j] - i;
                for(int k = 0; k <= upp; ++k) {
                    if(ff[k] == INF)
                        continue;
                    int kk = k + cc <= upp ? k + cc : upp, vv = ff[k] + w[j];
                    if(vv < ff[kk])
                        ff[kk] = vv;
                }
                for(int k = upp; k > 0; --k)
                    if(ff[k - 1] > ff[k])
                        ff[k - 1] = ff[k];
            }
        }
        long long ans = 0;
        for(int i = 0; i < n; ++i)
            if(f[b[i]][a[i]] < INF) {
                ans += f[b[i]][a[i]];
            } else {
                ans = -1;
                break;
            }
        printf("%I64d\n", ans);
    }
    return 0;
}