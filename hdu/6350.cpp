#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)2e5 + 1, maxd = 17;
int t, n, m, dsu[maxn], up[maxn], dep[maxn], tot, que[maxn];
int mx, sz[maxn], cnt[maxd][maxn];
vector<int> e[maxn], ord, adt;
struct Edge {
    int u, v, w;
    bool operator < (Edge const &t) const {
        return w > t.w;
    }
} seq[maxm];
int dsu_find(int u) {
    return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
bool dsu_merge(int u, int v) {
    u = dsu_find(u);
    v = dsu_find(v);
    if(u == v)
        return 0;
    if(dsu[u] < dsu[v])
        swap(u, v);
    dsu[v] -= dsu[u] == dsu[v];
    dsu[u] = v;
    return 1;
}
LL dsu_merge(int u, int v, int w) {
    u = dsu_find(u);
    v = dsu_find(v);
    assert(u != v);
    if(dsu[u] < dsu[v])
        swap(u, v);
    dsu[v] -= dsu[u] == dsu[v];
    dsu[u] = v;
    LL ret = 0;
    int &su = sz[u], &sv = sz[v];
    for(int i = 0; i < mx; ++i) {
        int &cu = cnt[i][u], &cv = cnt[i][v];
        if((w >> i) & 1)
            ret += ((LL)cu * cv + (LL)(su - cu) * (sv - cv)) << i;
        else
            ret += ((LL)cu * (sv - cv) + (LL)(su - cu) * cv) << i;
        cv += cu;
    }
    ret += ((LL)(w >> mx) * su * sv) << mx;
    sv += su;
    return ret;
}
void bfs(int rt) {
    tot = 0;
    que[tot++] = rt;
    for(int i = 0; i < tot; ++i) {
        int u = que[i];
        for(int it : e[u]) {
            if(it == up[u])
                continue;
            int v = u == seq[it].u ? seq[it].v : seq[it].u;
            up[v] = it;
            dep[v] = dep[u] + 1;
            que[tot++] = v;
        }
    }
}
namespace fastIO {
    #define BUF_SIZE (1 << 20 | 1)
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
};
int main() {
    fastIO::read(t);
    while(t--) {
        fastIO::read(n), fastIO::read(m);
        for(int i = 0; i < m; ++i)
            fastIO::read(seq[i].u), fastIO::read(seq[i].v), fastIO::read(seq[i].w);
        sort(seq, seq + m);
        memset(dsu + 1, -1, n * sizeof(int));
        for(int i = 0; i < m; ++i)
            if(dsu_merge(seq[i].u, seq[i].v)) {
                e[seq[i].u].push_back(i);
                e[seq[i].v].push_back(i);
                ord.push_back(i);
            } else {
                adt.push_back(i);
            }
        up[1] = -1;
        dep[1] = 0;
        bfs(1);
        for(int i : adt) {
            int u = seq[i].u, v = seq[i].v, w = seq[i].w;
            while(u != v) {
                if(dep[u] < dep[v])
                    swap(u, v);
                int j = up[u];
                seq[j].w += w;
                u = u == seq[j].u ? seq[j].v : seq[j].u;
            }
        }
        sort(ord.begin(), ord.end(), [&](int const &i, int const &j) {
            return seq[i].w > seq[j].w;
        });
        for( ; 1 << mx <= n; ++mx);
        for(int i = 1; i <= n; ++i) {
            dsu[i] = -1;
            sz[i] = 1;
            for(int j = 0; j < mx; ++j)
                cnt[j][i] = (i >> j) & 1;
        }
        LL ans = 0;
        for(int i : ord)
            ans += dsu_merge(seq[i].u, seq[i].v, seq[i].w);
        printf("%llu\n", ans);
        for(int i = 1; i <= n; ++i)
            vector<int>().swap(e[i]);
        vector<int>().swap(ord);
        vector<int>().swap(adt);
    }
    return 0;
}
