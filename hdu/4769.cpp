#include <cstdio>
#include <cstring>
#include <algorithm>
typedef unsigned UL;
typedef unsigned long long ULL;
const int maxn = 11, maxt = 7, maxm = 201, maxv = 61, maxr = 601, upp = 21;
const int maxs = ((maxr - 1) >> 6) + 1, maxd = 1 << 16 | 1, INF = 0x3f3f3f3f;
int t, n, m, rcnt, lbt[maxd], bits[maxm], tim[maxr], per[maxr], con[maxv], lim, ans;
bool vis[maxn][maxt];
int lowbit(UL x) {
    return x & 65535 ? lbt[x & 65535] : 16 | lbt[x >> 16];
}
int lowbit(ULL x) {
    return (UL)x ? lowbit((UL)x) : 32 | lowbit((UL)(x >> 32));
}
struct Bitset {
    int len;
    ULL data[maxs];
    void reset() {
        memset(data, 0, len * sizeof(ULL));
    }
    void flip(int pos) {
        data[pos >> 6] ^= 1ULL << (pos & 63);
    }
    bool test(int pos) const {
        return (data[pos >> 6] >> (pos & 63)) & 1;
    }
    void reset(int pos) {
        test(pos) && (flip(pos), 1);
    }
    void set(int pos) {
        test(pos) || (flip(pos), 1);
    }
    int lowbit(int low = 0) const {
        int px = low >> 6, py = low & 63;
        if(px < len && (data[px] >> py))
            return px << 6 | ::lowbit((data[px] >> py) << py);
        for(int i = px + 1; i < len; ++i)
            if(data[i])
                return i << 6 | ::lowbit(data[i]);
        return len << 6;
    }
    bool none() const {
        for(int i = 0; i < len; ++i)
            if(data[i])
                return 0;
        return 1;
    }
    Bitset operator | (Bitset const &t) const {
        Bitset ret = {std::min(len, t.len)};
        for(int i = 0; i < ret.len; ++i)
            ret.data[i] = data[i] | t.data[i];
        return ret;
    }
    Bitset operator - (Bitset const &t) const {
        Bitset ret = {std::min(len, t.len)};
        for(int i = 0; i < ret.len; ++i)
            ret.data[i] = data[i] & ~t.data[i];
        return ret;
    }
} curC[maxv], a[maxn][maxt], row[maxr], col[maxm];
int calc(int dep) {
    int ret = dep;
    Bitset tmp = curC[dep];
    for(int pos = tmp.lowbit(); pos < m; pos = tmp.lowbit(pos + 1)) {
        int sel = col[pos].lowbit();
        if(sel < rcnt) {
            for(++ret; sel < rcnt; sel = col[pos].lowbit(sel + 1))
                tmp = tmp - row[sel];
        } else {
            return INF;
        }
    }
    return ret;
}
void dfs(int dep, bool flag) {
    if(calc(dep) >= ans)
        return;
    if(curC[dep].none()) {
        ans = dep;
        return;
    }
    int pos = curC[dep].lowbit();
    for(int i = curC[dep].lowbit(pos + 1); i < m; i = curC[dep].lowbit(i + 1))
        if(bits[i] < bits[pos])
            pos = i;
    for(int sel = col[pos].lowbit(); sel < rcnt; sel = col[pos].lowbit(sel + 1)) {
        int tt = tim[sel], pp = per[sel];
        if(con[tt] != -1)
            continue;
        if(tt > 1 && con[tt - 1] == pp)
            continue;
        if(tt < lim && con[tt + 1] == pp)
            continue;
        con[tt] = pp;
        curC[dep + 1] = curC[dep] - row[sel];
        dfs(dep + 1, flag);
        con[tt] = -1;
        if(!flag && ans <= std::min(lim, upp))
            return;
    }
}
bool check(bool flag) {
    for(rcnt = 0; tim[rcnt] <= lim; ++rcnt);
    for(int i = 0; i < m; ++i) {
        col[i].len = ((rcnt - 1) >> 6) + 1;
        bits[i] = 0;
        for(int j = 0; j < rcnt; ++j)
            if(row[j].test(i))
                ++bits[i];
    }
    ans = std::min(lim, upp) + 1;
    memset(con + 1, -1, lim * sizeof(int));
    dfs(0, flag);
    return ans <= std::min(lim, upp);
}
int main() {
    for(int i = 1; i < maxd; ++i)
        lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        int mx = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 1; j < maxt; ++j)
                vis[i][j] = 0;
            int c, x, y;
            scanf("%d", &c);
            while(c--) {
                scanf("%d", &x);
                mx = std::max(mx, x);
                if(!vis[i][x]) {
                    vis[i][x] = 1;
                    a[i][x].len = ((m - 1) >> 6) + 1;
                    a[i][x].reset();
                }
                for(int j = 0; j < m; ++j) {
                    scanf("%d", &y);
                    if(y)
                        a[i][x].set(j);
                }
            }
            for(int j = 1; j < maxt; ++j)
                if(vis[i][j] && a[i][j].none())
                    vis[i][j] = 0;
        }
        int L = 1, R = std::max(n, mx) * mx;
        rcnt = 0;
        for(int i = 1; i <= R; ++i)
            for(int j = 0; j < n; ++j) {
                row[rcnt].len = ((m - 1) >> 6) + 1;
                row[rcnt].reset();
                for(int k = 1; k < maxt; ++k)
                    if(i % k == 0 && vis[j][k])
                        row[rcnt] = row[rcnt] | a[j][k];
                if(!row[rcnt].none()) {
                    tim[rcnt] = i;
                    per[rcnt] = j;
                    ++rcnt;
                }
            }
        tim[rcnt] = R + 1;
        curC[0].len = ((m - 1) >> 6) + 1;
        curC[0].reset();
        for(int i = 0; i < m; ++i) {
            curC[0].set(i);
            col[i].len = ((rcnt - 1) >> 6) + 1;
            col[i].reset();
            for(int j = 0; j < rcnt; ++j)
                if(row[j].test(i))
                    col[i].set(j);
        }
        while(L < R) {
            lim = (L + R) >> 1;
            if(check(0))
                R = lim;
            else
                L = lim + 1;
        }
        lim = L;
        if(check(1))
            printf("%d %d\n", lim, ans);
        else
            puts("0");
    }
    return 0;
}
