#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxN = 3003, maxM = 33001, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxN], cur[maxN], lev[maxN];
struct Edge {
    int nxt, v, w;
} e[maxM << 1 | 1];
void addEdge(int u, int v, int w) {
    e[M] = (Edge){lnk[u], v, w};
    lnk[u] = M++;
    e[M] = (Edge){lnk[v], u, 0};
    lnk[v] = M++;
}
bool bfs() {
    int L = 0, R = 0;
    static int que[maxN];
    memset(lev, -1, N * sizeof(int));
    lev[S] = 0;
    que[R++] = S;
    while(L < R) {
        int u = que[L++];
        for(int it = lnk[u]; it != -1; it = e[it].nxt)
            if(lev[e[it].v] == -1 && e[it].w) {
                lev[e[it].v] = lev[u] + 1;
                que[R++] = e[it].v;
            }
    }
    return lev[T] != -1;
}
int dfs(int u, int lim) {
    if(u == T) // || !lim
        return lim;
    int ret = 0, tmp;
    for(int &it = cur[u]; it != -1; it = e[it].nxt)
        if(lev[e[it].v] == lev[u] + 1 && e[it].w > 0
        && (tmp = dfs(e[it].v, min(lim - ret, e[it].w))) > 0) {
            e[it].w -= tmp;
            e[it ^ 1].w += tmp;
            if((ret += tmp) == lim)
                break;
        }
    if(!ret)
        lev[u] = -1;
    return ret;
}
const int maxl = 20, maxs = (maxl * maxl) | 1, maxc = 3, maxd = 1 << maxc | 1;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
int s[maxs], w[maxs], f[maxd][maxs];
priority_queue<pair<int, int> > Q;
bool vis[maxs];
void prepare(int &sz, int typ[], int cst[]) {
    sz = 0;
    for(int i = 0, idx = 0; i < maxl; ++i)
        for(int j = 0; j < maxl; ++j, ++idx) {
            int val;
            scanf("%d", &val);
            if(val == -1) {
                s[idx] = 1;
            } else if(val <= 1000) {
                s[idx] = 0;
            } else {
                if(val <= 101000) {
                    typ[sz++] = 100000 - val;
                } else if(val <= 201000) {
                    typ[sz++] = val - 200000;
                }
                s[idx] = 1 << sz;
            }
            w[idx] = val >= 0 && val <= 1000 ? val : 0;
        }
    if(!sz)
        return;
    memset(f, 0x3f, sizeof f);
    for(int idx = 0; idx < maxs - 1; ++idx)
        if(s[idx])
            f[s[idx]][idx] = 0;
    for(int msk = 0; msk < 2 << sz; ++msk) {
        int *dis = f[msk];
        memset(vis, 0, sizeof vis);
        for( ; !Q.empty(); Q.pop());
        for(int idx = 0; idx < maxs - 1; ++idx) {
            if(s[idx] && !(msk & s[idx]))
                continue;
            for(int msk2 = msk; msk2; msk2 = (msk2 - 1) & msk) {
                int tmp = f[msk2 | s[idx]][idx] + f[(msk ^ msk2) | s[idx]][idx] - w[idx];
                if(tmp < dis[idx])
                    dis[idx] = tmp;
            }
            if(dis[idx] < INF)
                Q.push(make_pair(-dis[idx], idx));
        }
        while(!Q.empty()) {
            int udx = Q.top().second;
            Q.pop();
            if(vis[udx])
                continue;
            vis[udx] = 1;
            int ux = udx / maxl, uy = udx % maxl;
            for(int i = 0; i < 4; ++i) {
                int vx = ux + dx[i], vy = uy + dy[i];
                if(!(vx >= 0 && vx < maxl && vy >= 0 && vy < maxl))
                    continue;
                int vdx = vx * maxl + vy, msk2 = msk | s[vdx], tmp = dis[udx] + w[vdx];
                if(tmp < f[msk2][vdx]) {
                    f[msk2][vdx] = tmp;
                    if(msk == msk2)
                        Q.push(make_pair(-dis[vdx], vdx));
                }
            }
        }
    }
    for(int idx = 0; idx < maxs - 1; ++idx)
        if(s[idx] > 1)
            cst[s[idx] == 2 ? 0 : 1] = f[s[idx] | 1][idx];
        else if(s[idx] == 1 && sz == 2)
            cst[2] = f[7][idx];
}
const int maxn = 30001, maxm = 1001;
int n, m, hp, a[maxn], b[maxn], d[maxn], sz[maxm], typ[maxm][maxc], cst[maxm][maxc];
bool va[maxn], vb[maxn];
int calc(int lim) {
    memset(lnk, -1, sizeof lnk);
    N = 2002;
    M = 0;
    S = 0;
    T = N - 1;
    memset(va, 0, sizeof va);
    memset(vb, 0, sizeof vb);
    for(int i = 0; i < lim; ++i) {
        if(sz[i] == 1) {
            if(typ[i][0] < 0) {
                addEdge(S, -typ[i][0], cst[i][0]);
            } else {
                addEdge(1000 + typ[i][0], T, cst[i][0]);
            }
        } else if(sz[i] == 2) {
            if(typ[i][0] < 0) {
                addEdge(S, N, cst[i][2]);
                addEdge(N, -typ[i][0], cst[i][0]);
                addEdge(N, -typ[i][1], cst[i][1]);
            } else {
                addEdge(1000 + typ[i][0], N, cst[i][0]);
                addEdge(1000 + typ[i][1], N, cst[i][1]);
                addEdge(N, T, cst[i][2]);
            }
            ++N;
        }
        for(int j = 0; j < sz[i]; ++j)
            if(typ[i][j] < 0)
                va[-typ[i][j]] = 1;
            else
                vb[typ[i][j]] = 1;
    }
    for(int i = 1; i <= 1000; ++i) {
        if(!va[i])
            addEdge(S, i, INF);
        if(!vb[i])
            addEdge(1000 + i, T, INF);
    }
    for(int i = 0; i < n; ++i)
        addEdge(a[i], 1000 + b[i], d[i]);
    int ret = 0, tmp;
    while(bfs()) {
        memcpy(cur, lnk, N * sizeof(int));
        for( ; (tmp = dfs(S, INF)) > 0; ret += tmp);
    }
    return ret;
}
int main() {
    while(scanf("%d%d%d", &n, &m, &hp) == 3) {
        for(int i = 0; i < n; ++i)
            scanf("%d%d%d", a + i, b + i, d + i);
        for(int i = 0; i < m; ++i)
            prepare(sz[i], typ[i], cst[i]);
        int L = 0, R = m;
        while(L < R) {
            int M = (L + R) >> 1;
            calc(M) < hp ? (R = M) : (L = M + 1);
        }
        int val = calc(L);
        if(val < hp)
            printf("%d %d\n", L, val);
        else
            puts("Impossible.");
    }
    return 0;
}