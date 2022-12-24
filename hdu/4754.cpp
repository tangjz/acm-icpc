#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 303, maxm = 90601, maxt = 61;
const DB eps = 1e-4, INF = 6e16;
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn];
struct Edge {
    int nxt, v;
    DB w;
} e[maxm << 1 | 1];
inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}
inline void addEdge(int u, int v, DB w, bool bij = 0) {
    e[M] = (Edge){lnk[u], v, w};
    lnk[u] = M++;
    e[M] = (Edge){lnk[v], u, bij ? w : 0};
    lnk[v] = M++;
}
bool bfs() {
    int L = 0, R = 0;
    static int que[maxn];
    memset(lev, -1, N * sizeof(int));
    lev[S] = 0;
    que[R++] = S;
    while(L < R) {
        int u = que[L++];
        for(int it = lnk[u]; it != -1; it = e[it].nxt)
            if(sgn(e[it].w) > 0 && lev[e[it].v] == -1) {
                lev[e[it].v] = lev[u] + 1;
                que[R++] = e[it].v;
            }
    }
    return lev[T] != -1;
}
DB dfs(int u, DB upp) {
    if(u == T)
        return upp;
    DB ret = 0, tmp;
    for(int &it = cur[u]; it != -1; it = e[it].nxt)
        if(lev[e[it].v] == lev[u] + 1 && sgn(e[it].w) > 0
        && sgn(tmp = dfs(e[it].v, std::min(upp - ret, e[it].w))) > 0) {
            e[it].w -= tmp;
            e[it ^ 1].w += tmp;
            if(!sgn((ret += tmp) - upp))
                break;
        }
    if(!sgn(ret))
        lev[u] = -1;
    return ret;
}
int n, m, c[2][2], sz[2];
LL sum[maxn], mx;
struct Node {
    int id, p;
    DB x, y;
} p[2][maxn];
struct Edge2 {
    int u, v;
    LL w;
} g[maxm];
bool solve(DB lambda) {
    N = n + 2;
    M = 0;
    S = N - 2;
    T = N - 1;
    memset(lnk, -1, N * sizeof(int));
    for(int i = 0; i < n; ++i) {
        addEdge(S, i, mx);
        addEdge(i, T, mx - sum[i] + 2 * lambda);
    }
    for(int i = 0; i < m; ++i)
        if(g[i].w)
            addEdge(g[i].u, g[i].v, g[i].w, 1);
    DB flow = 0;
    while(bfs()) {
        memcpy(cur, lnk, N * sizeof(int));
        for(DB tmp; sgn(tmp = dfs(S, INF)) > 0; flow += tmp);
    }
    return sgn(flow - mx * n) >= 0;
}
int cnt;
bool vis[maxn];
void pfs(int u) {
    vis[u] = 1;
    cnt -= u < n;
    for(int it = lnk[u]; it != -1; it = e[it].nxt)
        if(!vis[e[it].v] && sgn(e[it ^ 1].w) > 0)
            pfs(e[it].v);
}
inline DB sqr(DB x) {
    return x * x;
}
int main() {
    for(int Case = 1; scanf("%d%d%d%d", &n, &c[0][0], &c[0][1], &c[1][1]) == 4; ++Case) {
        c[1][0] = c[0][1];
        sz[0] = sz[1] = 0;
        memset(sum, 0, n * sizeof(LL));
        int low = 0;
        for(int i = 0; i < n; ++i) {
            char op;
            scanf(" %c", &op);
            int typ = op == 'k';
            Node &cur = p[typ][++sz[typ]];
            cur.id = i;
            double r, a;
            scanf("%lf%lf%d", &r, &a, &cur.p);
            cur.x = r * cos((DB)a);
            cur.y = r * sin((DB)a);
            sum[i] += cur.p << 1;
            low = max(low, cur.p);
        }
        scanf("%d", &m);
        LL upp = low;
        for(int i = 0; i < m; ++i) {
            char op1, op2;
            int idx1, idx2;
            scanf(" %c%d %c%d", &op1, &idx1, &op2, &idx2);
            int typ1 = op1 == 'k', typ2 = op2 == 'k';
            Node &u = p[typ1][idx1], &v = p[typ2][idx2];
            g[i].u = u.id;
            g[i].v = v.id;
            g[i].w = (LL)round(sqrt(sqr(u.x - v.x) + sqr(u.y - v.y))) * c[typ1][typ2];
            sum[g[i].u] += g[i].w;
            sum[g[i].v] += g[i].w;
            upp += g[i].w;
        }
        mx = 0;
        for(int i = 0; i < n; ++i)
            mx = max(mx, sum[i]);
        DB L = low, R = upp;
        for(int i = 0; i < maxt; ++i) {
            DB M = L + (R - L) * 0.5;
            if(solve(M)) {
                R = M;
                cnt = n;
                memset(vis, 0, N * sizeof(bool));
                pfs(T);
            } else {
                L = M;
            }
        }
        LL ans = 0;
        for(int i = 0; i < 2; ++i)
            for(int j = 1; j <= sz[i]; ++j)
                if(!vis[p[i][j].id])
                    ans += p[i][j].p;
        for(int i = 0; i < m; ++i)
            if(!vis[g[i].u] && !vis[g[i].v])
                ans += g[i].w;
        printf("Case #%d: %.4f %d\n", Case, ans / (double)cnt, cnt);
    }
    return 0;
}