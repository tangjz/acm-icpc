#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 300001, mod = 998244353;
int t, n, tot, lnk[maxn << 1 | 1], deg[maxn << 1 | 1], que[maxn << 1 | 1], L, R, ans, prd[2];
struct Edge {
    int nxt, v, w;
} e[maxn << 2 | 1];
bool ban[maxn << 1 | 1];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(lnk + 1, -1, (n << 1) * sizeof(int));
        memset(deg + 1, 0, (n << 1) * sizeof(int));
        tot = 0;
        for(int i = 1; i <= n; ++i) {
            int v1, w1, v2, w2;
            scanf("%d%d%d%d", &v1, &w1, &v2, &w2);
            e[tot] = (Edge){lnk[n + i], v1, w1};
            lnk[n + i] = tot++;
            ++deg[n + i];
            e[tot] = (Edge){lnk[v1], n + i, w1};
            lnk[v1] = tot++;
            ++deg[v1];
            e[tot] = (Edge){lnk[n + i], v2, w2};
            lnk[n + i] = tot++;
            ++deg[n + i];
            e[tot] = (Edge){lnk[v2], n + i, w2};
            lnk[v2] = tot++;
            ++deg[v2];
        }
        L = R = 0;
        for(int i = 1; i <= n; ++i)
            if(deg[i] == 1)
                que[R++] = i;
        memset(ban, 0, (tot >> 1) * sizeof(bool));
        ans = 1;
        while(L < R) {
            int u = que[L++], v;
            if(!deg[u])
                continue;
            for(int &it = lnk[u]; it != -1; it = e[it].nxt)
                if(!ban[it >> 1]) {
                    v = e[it].v;
                    ans = (LL)ans * e[it].w % mod;
                    break;
                }
            for(int &it = lnk[v]; it != -1; it = e[it].nxt) {
                ban[it >> 1] = 1;
                if((--deg[e[it].v]) == 1)
                    que[R++] = e[it].v;
            }
            deg[v] = 0;
        }
        for(int i = 1; i <= n; ++i) {
            if(!deg[i])
                continue;
            prd[0] = prd[1] = 1;
            L = R = 0;
            que[R++] = i;
            for( ; L < R; ++L) {
                int u = que[L];
                for(int &it = lnk[u]; it != -1; it = e[it].nxt)
                    if(!ban[it >> 1]) {
                        --deg[u];
                        --deg[e[it].v];
                        ban[it >> 1] = 1;
                        prd[L & 1] = (LL)prd[L & 1] * e[it].w % mod;
                        que[R++] = e[it].v;
                        break;
                    }
            }
            ans = (LL)ans * (prd[0] + prd[1]) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}