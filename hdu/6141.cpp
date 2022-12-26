#include <cstdio>
#include <cstring>
const int maxn = 1001, maxm = 10001, INF = 0x3f3f3f3f;
int t, n, m, pre[maxn], val[maxn], tim[maxn], idx[maxn];
struct Edge {
    int u, v, w;
} e[maxm];
int solve(int n, int rt) {
    int ret = 0;
    while(1) {
        memset(val, 0x3f, n * sizeof(int));
        for(int i = 0; i < m; ++i)
            if(e[i].u != e[i].v && e[i].w < val[e[i].v]) {
                val[e[i].v] = e[i].w;
                pre[e[i].v] = e[i].u;
            }
        val[rt] = 0;
        for(int i = 0; i < n; ++i)
            if(val[i] == INF)
                return INF;
        memset(tim, -1, n * sizeof(int));
        memset(idx, -1, n * sizeof(int));
        int cnt = 0;
        tim[rt] = rt;
        for(int i = 0, j; i < n; ++i) {
            ret += val[i];
            for(j = i; tim[j] == -1; j = pre[j])
                tim[j] = i;
            if(j != rt && tim[j] == i) {
                for(int k = pre[j]; k != j; k = pre[k])
                    idx[k] = cnt;
                idx[j] = cnt++;
            }
        }
        if(!cnt)
            return ret;
        for(int i = 0; i < n; ++i)
            if(idx[i] == -1)
                idx[i] = cnt++;
        for(int i = 0, j; i < m; ++i) {
            j = e[i].v;
            e[i].u = idx[e[i].u];
            e[i].v = idx[e[i].v];
            if(e[i].u != e[i].v)
                e[i].w -= val[j];
        }
        n = cnt;
        rt = idx[rt];
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
            e[i].w = -e[i].w * n + (e[i].v == n ? e[i].u : 0);
            --e[i].u;
            --e[i].v;
        }
        int ans = -solve(n, 0), id = n - ans % n;
        ans = (ans + id) / n;
        printf("%d %d\n", ans, id);
    }
    return 0;
}
