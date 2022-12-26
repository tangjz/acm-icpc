#include <bits/stdc++.h>
using namespace std;

const int maxd = 10, maxn = (int)1e3 + 1, maxm = (int)7e3 + 1;

int n, m, s, t, lnk[maxn], ptr[maxn], pos[maxn];
struct Edge {
    int nxt, v, w;
} e[maxm];

int new_node() {
    lnk[n] = -1;
    return n++;
}
void add_edge(int u, int v, int w) {
    e[m] = (Edge){lnk[u], v, w};
    lnk[u] = m++;
    e[m] = (Edge){lnk[v], u, w};
    lnk[v] = m++;
}
bool bfs() {
    static int que[maxn];
    memset(pos, -1, n * sizeof(int));
    pos[s] = 0;
    que[0] = s;
    for(int i = 0, sz = 1; i < sz; ++i) {
        int u = que[i];
        for(int it = lnk[u]; it != -1; it = e[it].nxt)
            if(e[it].w > 0 && pos[e[it].v] == -1) {
                pos[e[it].v] = pos[u] + 1;
                if(e[it].v == t)
                    return 1;
                que[sz++] = e[it].v;
            }
    }
    return 0;
}
int dfs(int u, int lim) {
    if(u == t || !lim)
        return lim;
    int ret = 0, adt;
    for(int &it = ptr[u]; it != -1; it = e[it].nxt) {
        if(pos[e[it].v] == pos[u] + 1 && e[it].w > 0 && (adt = dfs(e[it].v, min(e[it].w, lim - ret))) > 0) {
            e[it].w -= adt;
            e[it ^ 1].w += adt;
            ret += adt;
            if(ret == lim)
                break;
        }
    }
    if(!ret)
        pos[u] = -1;
    return ret;
}

void solve() {
    int q;
    static int idx[maxd + 1][maxd + 1][maxd + 1];
    memset(idx, -1, sizeof idx);
    n = m = 0;
    s = new_node();
    t = new_node();
    scanf("%d", &q);
    while(q--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        idx[x][y][z] = s;
    }
    for(int x = 0; x < maxd; ++x)
        for(int y = 0; y < maxd; ++y)
            for(int z = 0; z < maxd; ++z) {
                if(idx[x][y][z] == -1)
                    idx[x][y][z] = new_node();
                int u = idx[x][y][z], seq[3] = {x ? idx[x - 1][y][z] : t, y ? idx[x][y - 1][z] : t, z ? idx[x][y][z - 1] : t};
                int cs = 0, ct = (x + 1 == maxd) + (y + 1 == maxd) + (z + 1 == maxd);
                for(int v: seq) {
                    if(v != s && v != t) {
                        add_edge(u, v, 1);
                        continue;
                    }
                    cs += v == s;
                    ct += v == t;
                }
                if(cs)
                    add_edge(u, s, cs);
                if(ct)
                    add_edge(u, t, ct);
            }
    int ans = 0, adt;
    while(bfs()) {
        memcpy(ptr, lnk, n * sizeof(int));
        adt = dfs(s, maxm);
        if(!adt)
            break;
        ans += adt;
    }
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
