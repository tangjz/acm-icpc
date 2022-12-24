#include <cstdio>
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
};
typedef long long LL;
const int maxn = 200001;
int n, c[maxn], lnk[maxn], pos[maxn], ctr[maxn], rem[maxn];
LL ans;
struct Edge {
    int nxt, v;
} e[maxn << 1 | 1];
inline LL sum2(int x) {
    return (x * (x - 1LL)) >> 1;
}
int dfs(int u, int fa) {
    int su = 1, o = pos[c[u]];
    pos[c[u]] = u;
    for(int it = lnk[u]; it; it = e[it].nxt)
        if(e[it].v != fa) {
            ctr[u] = 0;
            int sv = dfs(e[it].v, u);
            ans -= sum2(sv - ctr[u]);
            su += sv;
        }
    (o ? ctr[o] : rem[c[u]]) += su;
    pos[c[u]] = o;
    return su;
}
int main() {
    for(int Case = 1; fastIO::read(n), !fastIO::IOerror; ++Case) {
        for(int i = 1; i <= n; ++i) {
            fastIO::read(c[i]);
            lnk[i] = rem[i] = 0;
        }
        for(int i = 1, u, v; i < n; ++i) {
            fastIO::read(u);
            fastIO::read(v);
            e[i << 1] = (Edge){lnk[u], v};
            lnk[u] = i << 1;
            e[i << 1 | 1] = (Edge){lnk[v], u};
            lnk[v] = i << 1 | 1;
        }
        ans = sum2(n) * n;
        dfs(1, -1);
        for(int i = 1; i <= n; ++i)
            ans -= sum2(n - rem[i]);
        printf("Case #%d: %I64d\n", Case, ans);
    }
    return 0;
}