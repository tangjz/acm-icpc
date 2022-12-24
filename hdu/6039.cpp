#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
const double log_2 = log(2);
namespace fastIO {
    #define BUF_SIZE 100000
    //fread -> read
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
    #undef BUF_SIZE
} using namespace fastIO;
int n, m, q, a[maxn], dsu[maxn], tot, lnk[maxn], lst[maxn];
int rt, idx[maxn], in[maxn], out[maxn];
int pL[maxn], pR[maxn], qL[maxn], qR[maxn];
inline int dsu_find(int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
inline void dsu_merge(int u, int v) {
    u = dsu_find(u);
    v = dsu_find(v);
    if(u == v)
        return;
    if(dsu[u] < dsu[v])
        std::swap(u, v);
    if(dsu[u] == dsu[v])
        --dsu[v];
    dsu[u] = v;
}
struct Edge {
    int nxt, v;
} e[maxn << 1 | 1], g[maxn << 1 | 1];
struct Segment {
    int val, tag;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}
inline void seg_up(int rt, int lch, int rch) {
    seg[rt].val = std::max(seg[lch].val, seg[rch].val);
}
inline void seg_down(int rt, int lch, int rch) {
    if(seg[rt].tag) {
        int &tag = seg[rt].tag;
        seg[lch].val += tag;
        seg[lch].tag += tag;
        seg[rch].val += tag;
        seg[rch].tag += tag;
        tag = 0;
    }
}
void seg_build(int L, int R) {
    int rt = seg_idx(L, R);
    seg[rt].tag = 0;
    if(L == R)
        return;
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    seg_build(L, M);
    seg_build(M + 1, R);
    seg_up(rt, lch, rch);
}
int seg_get(int L, int R, int x) {
    int rt = seg_idx(L, R);
    if(L == R)
        return seg[rt].val;
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    seg_down(rt, lch, rch);
    int ret = x <= M ? seg_get(L, M, x) : seg_get(M + 1, R, x);
    seg_up(rt, lch, rch);
    return ret;
}
int seg_max(int L, int R, int l, int r) {
    int rt = seg_idx(L, R);
    if(l <= L && R <= r)
        return seg[rt].val;
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    seg_down(rt, lch, rch);
    int ret = r <= M ? seg_max(L, M, l, r) : (M < l ? seg_max(M + 1, R, l, r) : std::max(seg_max(L, M, l, r), seg_max(M + 1, R, l, r)));
    seg_up(rt, lch, rch);
    return ret;
}
void seg_upd(int L, int R, int l, int r, int v) {
    int rt = seg_idx(L, R);
    if(l <= L && R <= r) {
        seg[rt].val += v;
        seg[rt].tag += v;
        return;
    }
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    seg_down(rt, lch, rch);
    if(l <= M)
        seg_upd(L, M, l, r, v);
    if(M < r)
        seg_upd(M + 1, R, l, r, v);
    seg_up(rt, lch, rch);
}
void dfs(int u, int fa, int dt) {
    idx[u] = rt;
    in[u] = ++tot;
    seg[seg_idx(tot, tot)].val = dt;
    for(int it = lst[u]; it != -1; it = g[it].nxt) {
        int x = g[it].v;
        pL[x] = tot + 1;
        for(int jt = lnk[x]; jt != -1; jt = e[jt].nxt) {
            int y = e[jt].v, v = dsu_find(y); // edge: x (belong to u) -> y (belong to v)
            if(v == fa)
                continue;
            qL[y] = tot + 1;
            dfs(v, u, dt + a[x] - a[y]);
            qR[y] = tot;
        }
        pR[x] = tot;
    }
    out[u] = tot;
}
int main() { // fastIO required
    for(int Case = 1; read(n), read(m), read(q), !IOerror; ++Case) {
        tot = 0;
        for(int i = 1, x; i <= n; ++i) {
            read(x);
            for(a[i] = 0; (1 << a[i]) < x; ++a[i]);
            dsu[i] = lnk[i] = lst[i] = in[i] = pR[i] = qR[i] = -1;
            pL[i] = qL[i] = 0;
        }
        while(m--) {
            int typ, u, v;
            read(typ), read(u), read(v);
            if(typ == 1) {
                e[tot] = (Edge){lnk[u], v};
                lnk[u] = tot++;
                e[tot] = (Edge){lnk[v], u};
                lnk[v] = tot++;
            } else {
                dsu_merge(u, v);
            }
        }
        tot = 0;
        for(int i = 1; i <= n; ++i) {
            int u = dsu_find(i);
            g[tot] = (Edge){lst[u], i};
            lst[u] = tot++;
        }
        tot = 0;
        for(int i = 1; i <= n; ++i)
            if(dsu[i] < 0 && in[i] == -1) {
                rt = i;
                dfs(i, -1, 0);
            }
        seg_build(1, tot);
        printf("Case #%d:\n", Case);
        while(q--) {
            int typ, x, y, z;
            read(typ), read(x), read(z);
            for(y = 0; (1 << y) < z; ++y);
            if(typ == 1) {
                y -= a[x];
                a[x] += y;
                if(pL[x] <= pR[x])
                    seg_upd(1, tot, pL[x], pR[x], y);
                if(qL[x] <= qR[x])
                    seg_upd(1, tot, qL[x], qR[x], -y);
            } else {
                x = dsu_find(x);
                printf("%.3f\n", (y - seg_get(1, tot, in[x]) + seg_max(1, tot, in[idx[x]], out[idx[x]])) * log_2);
            }
        }
    }
    return 0;
}