#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17;
int t, n, m, lnk[maxn], rdep[maxn], mx, rfa[maxd][maxn];
struct Edge {
    int nxt, v;
} e[maxn << 1 | 1];
bool ban[maxn];
int tot, ord[maxn], fa[maxn], dep[maxn];
void bfs(int rt) { // fa[rt], dep[rt] have been set
    tot = 0;
    ord[tot++] = rt;
    for(int i = 0; i < tot; ++i) {
        int u = ord[i];
        for(int it = lnk[u]; it != -1; it = e[it].nxt) {
            int v = e[it].v;
            if(v == fa[u] || ban[v])
                continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            ord[tot++] = v;
        }
    }
}
int ptot, idx[maxd][maxn], idx2[maxd][maxn], dis[maxd][maxn];
int len[maxn << 1 | 1], *cnt[maxn << 1 | 1];
int pool[(maxn * maxd) << 1 | 1], *tail;
int sz[maxn];
void build(int depth, int rt) {
    assert(depth < mx);
    fa[rt] = dep[rt] = 0;
    bfs(rt);
    int val = maxn;
    rt = -1;
    for(int i = tot - 1; i >= 0; --i) {
        int u = ord[i], mx = 0;
        sz[u] = 1;
        for(int it = lnk[u]; it != -1; it = e[it].nxt) {
            int v = e[it].v;
            if(v == fa[u] || ban[v])
                continue;
            mx = max(mx, sz[v]);
            sz[u] += sz[v];
        }
        mx = max(mx, tot - sz[u]);
        if(mx < val) {
            val = mx;
            rt = u;
        }
    }
    int pid = ptot++;
    idx[depth][rt] = idx2[depth][rt] = pid;
    dis[depth][rt] = fa[rt] = dep[rt] = 0;
    len[pid] = 1;
    for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
        int tr = e[it].v;
        if(ban[tr])
            continue;
        fa[tr] = rt;
        dep[tr] = dep[rt] + 1;
        bfs(tr);
        int cid = ptot++;
        len[cid] = dep[ord[tot - 1]] + 1;
        cnt[cid] = tail;
        tail += len[cid];
        assert(tail - pool <= (maxn * maxd << 1));
        memset(cnt[cid], 0, len[cid] * sizeof(int));
        len[pid] = max(len[pid], len[cid]);
        for(int i = 0; i < tot; ++i) {
            int u = ord[i];
            idx[depth][u] = pid;
            idx2[depth][u] = cid;
            dis[depth][u] = dep[u];
            ++cnt[cid][dep[u]];
        }
    }
    cnt[pid] = tail;
    tail += len[pid];
    assert(tail - pool <= (maxn * maxd << 1));
    memset(cnt[pid], 0, len[pid] * sizeof(int));
    for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
        int tr = e[it].v;
        if(ban[tr])
            continue;
        int cid = idx2[depth][tr];
        for(int i = 1; i < len[cid]; ++i) {
            cnt[pid][i] += cnt[cid][i];
            cnt[cid][i] += cnt[cid][i - 1];
        }
    }
    cnt[pid][0] = 1; // because dis[depth][rt] = 0
    for(int i = 1; i < len[pid]; ++i)
        cnt[pid][i] += cnt[pid][i - 1];
    ban[rt] = 1;
    for(int it = lnk[rt]; it != -1; it = e[it].nxt) {
        int tr = e[it].v;
        if(!ban[tr])
            build(depth + 1, tr);
    }
}
int query(int u, int w) {
    int ret = 0;
    for(int i = 0; ; ++i) {
        int pid = idx[i][u], cid = idx2[i][u], dt = w - dis[i][u];
        if(dt >= 0 && len[pid])
            ret += cnt[pid][min(dt, len[pid] - 1)];
        if(pid == cid)
            break;
        if(dt >= 0 && len[cid])
            ret -= cnt[cid][min(dt, len[cid] - 1)];
    }
    return ret;
}
int query(int u, int v, int w) {
    if(w < 0)
        return 0;
    if(u == v)
        return query(u, w);
    int ret = 0;
    bool chku = 1, chkv = 1;
    for(int i = 0; chku || chkv; ++i) {
        int pidu = idx[i][u], cidu = idx2[i][u], dtu = w - dis[i][u];
        int pidv = idx[i][v], cidv = idx2[i][v], dtv = w - dis[i][v];
        if(chku && chkv && pidu == pidv) {
            dtu = dtv = max(dtu, dtv);
            if(dtu >= 0 && len[pidu])
                ret += cnt[pidu][min(dtu, len[pidu] - 1)];
        } else {
            if(chku && dtu >= 0 && len[pidu])
                ret += cnt[pidu][min(dtu, len[pidu] - 1)];
            if(chkv && dtv >= 0 && len[pidv])
                ret += cnt[pidv][min(dtv, len[pidv] - 1)];
        }
        chku &= pidu != cidu;
        chkv &= pidv != cidv;
        if(chku && chkv && cidu == cidv) {
            if(dtu >= 0 && len[cidu])
                ret -= cnt[cidu][min(dtu, len[cidu] - 1)];
        } else {
            if(chku && dtu >= 0 && len[cidu])
                ret -= cnt[cidu][min(dtu, len[cidu] - 1)];
            if(chkv && dtv >= 0 && len[cidv])
                ret -= cnt[cidv][min(dtv, len[cidv] - 1)];
        }
    }
    return ret;
}
int lca(int u, int v) {
    for(int i = 0, j = rdep[u] - rdep[v]; j > 0; ++i, j >>= 1)
        (j & 1) && (u = rfa[i][u]);
    for(int i = 0, j = rdep[v] - rdep[u]; j > 0; ++i, j >>= 1)
        (j & 1) && (v = rfa[i][v]);
    if(u == v)
        return u;
    for(int i = mx - 1; i >= 0; --i)
        if(rfa[i][u] != rfa[i][v]) {
            u = rfa[i][u];
            v = rfa[i][v];
        }
    return rfa[0][u];
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        tot = 0;
        memset(lnk + 1, -1, n * sizeof(int));
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[tot] = (Edge){lnk[u], v};
            lnk[u] = tot++;
            e[tot] = (Edge){lnk[v], u};
            lnk[v] = tot++;
        }
        memset(ban + 1, 0, n * sizeof(bool));
        fa[1] = dep[1] = 0;
        bfs(1);
        memcpy(rdep + 1, dep + 1, n * sizeof(int));
        memcpy(rfa[0] + 1, fa + 1, n * sizeof(int));
        for(mx = 1; 1 << mx <= n; ++mx)
            for(int i = 1; i <= n; ++i)
                rfa[mx][i] = rfa[mx - 1][rfa[mx - 1][i]];
        ptot = 0;
        tail = pool;
        build(0, 1);
        int ans = 0;
        while(m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u = (u + ans) % n + 1;
            v = (v + ans) % n + 1;
            w = (w + ans) % n;
            int pp = lca(u, v), dt = rdep[u] + rdep[v] - (rdep[pp] << 1);
            int x = rdep[u] < rdep[v] ? v : u;
            for(int i = 0, j = dt >> 1; j > 0; ++i, j >>= 1)
                (j & 1) && (x = rfa[i][x]);
            int y = dt & 1 ? rfa[0][x] : x;
            printf("%d\n", ans = query(u, w) + query(v, w) - query(x, y, w - ((dt + 1) >> 1)));
        }
    }
    return 0;
}
