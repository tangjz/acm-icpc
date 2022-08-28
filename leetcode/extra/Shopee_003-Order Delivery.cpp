#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
namespace Flow {
    const int maxn = 45, maxm = 409;
    const LL INF = 0x3f3f3f3f3f3f3f3fLL;
    int N, M, S, T, lnk[maxn], flow;
    LL dis[maxn], sum, cost;
    struct Edge { int nxt, v, w; LL c; } e[maxm << 1 | 1];
    bool vis[maxn];
    void addEdge(int u, int v, int w, LL c) {
        // printf("edge %d -> %d: (%d, %lld)\n", u, v, w, c);
        e[M] = (Edge){lnk[u], v, w, c}; lnk[u] = M++;
        e[M] = (Edge){lnk[v], u, 0, -c}; lnk[v] = M++;
    }
    bool SPFA() {
        int L = 0, R = 0; static int que[maxn];
        memset(dis, 0x3f, N * sizeof(LL));
        memset(vis, 0, N * sizeof(bool));
        dis[T] = 0, vis[T] = 1, que[R++] = T;
        while(L != R) {
            int u = que[L++]; vis[u] = 0;
            L == maxn && (L = 0);
            for(int it = lnk[u]; it != -1; it = e[it].nxt) {
                if(!e[it ^ 1].w) continue;
                int v = e[it].v;
                LL tp = dis[u] + e[it ^ 1].c;
                if(tp < dis[v]) {
                    dis[v] = tp;
                    if(!vis[v]) {
                        que[R++] = v; vis[v] = 1;
                        R == maxn && (R = 0);
                    }
                }
            }
        }
        if(dis[S] == INF) return 0;
        for(int u = 0; u < N; ++u)
            for(int it = lnk[u]; it != -1; it = e[it].nxt)
                e[it].c += dis[e[it].v] - dis[u];
        return sum += dis[S], 1;
    }
    bool Dijkstra() {
        priority_queue<pair<LL, int> > Q;
        memset(dis, 0x3f, N * sizeof(LL));
        memset(vis, 0, N * sizeof(bool));
        dis[T] = 0; Q.push(make_pair(-dis[T], T));
        while(!Q.empty()) {
            int u = Q.top().second; Q.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(int it = lnk[u]; it != -1; it = e[it].nxt) {
                if(!e[it ^ 1].w) continue;
                int v = e[it].v;
                LL tp = dis[u] + e[it ^ 1].c;
                if(tp < dis[v]) {
                    dis[v] = tp;
                    Q.push(make_pair(-dis[v], v));
                }
            }
        }
        if(dis[S] == INF) return 0;
        for(int u = 0; u < N; ++u)
            for(int it = lnk[u]; it != -1; it = e[it].nxt)
                e[it].c += dis[e[it].v] - dis[u];
        return sum += dis[S], 1;
    }
    int dfs(int u, int upp) {
        if(u == T) return upp;
        vis[u] = 1;
        int ret = 0, tmp;
        for(int it = lnk[u]; it != -1; it = e[it].nxt)
            if(!e[it].c && !vis[e[it].v] && e[it].w
            && (tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
                e[it].w -= tmp; e[it ^ 1].w += tmp;
                if((ret += tmp) == upp)
                    break;
            }
        return ret;
    }
    void minCost(int upp = ~0u >> 1) {
        SPFA();
        do while(upp > 0) {
            memset(vis, 0, N * sizeof(bool));
            int adt = dfs(S, upp);
            if(!adt) break;
            upp -= adt; flow += adt;
            cost += adt * sum;
        } while(Dijkstra());
    }
    LL solve(int n, vector<vector<int> > &dis, vector<vector<pair<int, int> > > &cap, vector<int> &req) {
        N = n + n + 2, S = N - 2, T = N - 1;
        M = sum = flow = cost = 0;
        memset(lnk, -1, N * sizeof(int));
        int idx = 0;
        for(int i = 0; i < n; ++i) {
            for(auto &it: cap[i]) {
                addEdge(S, idx, it.first, 0);
                for(int j = 0; j < n; ++j)
                    if(req[j])
                        addEdge(idx, n + j, it.first, dis[i][j] * it.second);
                ++idx;
            }
            if(req[i])
                addEdge(n + i, T, req[i], 0);
        }
        minCost();
        return cost;
    }
}

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &q, &m);
    vector<vector<int> > dis(n, vector<int>(n, n));
    for(int i = 0; i < n; ++i)
        dis[i][i] = 0;
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        dis[u][v] = dis[v][u] = 1;
    }
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    vector<vector<pair<int, int> > > cap(n);
    while(q--) {
        int w, c, p;
        scanf("%d%d%d", &w, &c, &p);
        cap[--p].push_back({w, c});
    }
    vector<int> req(n);
    scanf("%d", &m);
    while(m--) {
        int k, g;
        scanf("%d%d", &k, &g);
        req[--g] += k;
    }
    printf("%lld\n", Flow::solve(n, dis, cap, req));
    return 0;
}
