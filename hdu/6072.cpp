#include <cstdio>
typedef unsigned long long ULL;
const int maxn = 251, maxs = 1 << 16 | 1;
int t, n, m, lbt[maxs], tot, seq[maxn], ans;
inline int lowbit(unsigned msk) {
    return msk & 65535 ? lbt[msk & 65535] : 16 + lbt[msk >> 16];
}
inline int lowbit(ULL msk) {
    return msk & 4294967295ULL ? lowbit((unsigned)msk) : 32 + lowbit((unsigned)(msk >> 32));
}
struct Bitset {
    ULL data[4];
    void clear() {
        data[0] = data[1] = data[2] = data[3] = 0;
    }
    bool test(int pos) const {
        return (data[pos >> 6] >> (pos & 63)) & 1;
    }
    void flip(int pos) {
        data[pos >> 6] ^= 1ULL << (pos & 63);
    }
    bool operator == (Bitset const &t) const {
        return data[0] == t.data[0] && data[1] == t.data[1] && data[2] == t.data[2] && data[3] == t.data[3];
    }
    Bitset operator - (Bitset const &t) const {
        return (Bitset){data[0] & (~t.data[0]), data[1] & (~t.data[1]), data[2] & (~t.data[2]), data[3] & (~t.data[3])};
    }
    int lowbit() const {
        return data[0] ? ::lowbit(data[0]) : data[1] ? 64 + ::lowbit(data[1]) : data[2] ? 128 + ::lowbit(data[2]) : data[3] ? 192 + ::lowbit(data[3]) : 256;
    }
} e[maxn], g[maxn], cur;
char buf[maxn];
void dfs1(int u) {
    cur.flip(u);
    for(int v = (e[u] - cur).lowbit(); v < n; v = (e[u] - cur).lowbit())
        dfs1(v);
    seq[--tot] = u;
}
void dfs2(int u) {
    ++tot;
    cur.flip(u);
    for(int v = (g[u] - cur).lowbit(); v < n; v = (g[u] - cur).lowbit())
        dfs2(v);
}
int main() {
    lbt[0] = -1;
    for(int i = 1; i < maxs; ++i)
        lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            e[i].clear();
            g[i].clear();
        }
        for(int i = 0; i < n; ++i) {
            scanf("%s", buf);
            for(int j = 0; j < n; ++j)
                if(buf[j] == '1') {
                    e[i].flip(j);
                    g[j].flip(i);
                }
        }
        while(m--) {
            int c, u, v;
            scanf("%d", &c);
            while(c--) {
                scanf("%d%d", &u, &v);
                --u;
                --v;
                e[u].flip(v);
                g[v].flip(u);
            }
            tot = n;
            cur.clear();
            for(int i = 0; i < n; ++i)
                if(!cur.test(i))
                    dfs1(i);
            ans = 0;
            cur.clear();
            for(int i = 0; i < n; ++i)
                if(!cur.test(seq[i])) {
                    tot = 0;
                    dfs2(seq[i]);
                    ans += (tot * (tot - 1)) >> 1;
                }
            printf("%d\n", ans);
        }
    }
    return 0;
}