#include <cstdio>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 100001;
const DB INF = 1e18, eps = 5e-7;
int t, n, m, a[maxn], b[maxn], w[maxn], ord[maxn], tot, que[maxn], pos[maxn], sp;
struct Segment {
    DB min, max;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}
void seg_init(int L, int R) {
    int rt = seg_idx(L, R);
    seg[rt].min = INF;
    seg[rt].max = -INF;
    if(L == R)
        return;
    int M = (L + R) >> 1;
    seg_init(L, M);
    seg_init(M + 1, R);
}
void seg_upd(int L, int R, int x, DB v) {
    int rt = seg_idx(L, R);
    seg[rt].min = std::min(seg[rt].min, v);
    seg[rt].max = std::max(seg[rt].max, v);
    if(L == R)
        return;
    int M = (L + R) >> 1;
    if(x <= M)
        seg_upd(L, M, x, v);
    else
        seg_upd(M + 1, R, x, v);
}
Segment seg_que(int L, int R, int l, int r) {
    if(l <= L && R <= r)
        return seg[seg_idx(L, R)];
    int M = (L + R) >> 1;
    if(r <= M)
        return seg_que(L, M, l, r);
    if(M < l)
        return seg_que(M + 1, R, l, r);
    Segment tL = seg_que(L, M, l, r), tR = seg_que(M + 1, R, l, r);
    tL.min = std::min(tL.min, tR.min);
    tL.max = std::max(tL.max, tR.max);
    return tL;
}
bool check(DB tim) {
    seg_init(1, tot);
    for(int i = 0, j; i < n; ) {
        for(j = i; j < n && w[ord[i]] == w[ord[j]]; ++j) {
            int o = ord[j];
            DB dis = a[o] + b[o] * tim;
            if(w[ord[0]] > w[o]) {
                Segment res = seg_que(1, tot, 1, pos[o]);
                if(res.max - dis < 0 && res.min - dis + m > 0) {
                    res = pos[o] < tot ? seg_que(1, tot, pos[o] + 1, tot) : (Segment){INF, -INF};
                    if(res.min - dis > 0 && res.max - dis - m < 0) {
                        sp = o;
                        return 0;
                    }
                }
            }
        }
        for( ; i < j; ++i) {
            int o = ord[i];
            DB dis = a[o] + b[o] * tim;
            seg_upd(1, tot, pos[o], dis);
        }
    }
    return 1;
}
bool cmp(int const &x, int const &y) {
    return w[x] > w[y];
}
int main() {
    scanf("%d", &t);
    while(t--) {
        tot = 0;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) {
            scanf("%d", a + i);
            que[tot++] = a[i];
        }
        std::sort(que, que + tot);
        tot = std::unique(que, que + tot) - que;
        for(int i = 0; i < n; ++i) {
            scanf("%d", b + i);
            pos[i] = std::lower_bound(que, que + tot, a[i]) - que + 1;
        }
        for(int i = 0; i < n; ++i) {
            scanf("%d", w + i);
            ord[i] = i;
        } // otherwise answer > 0
        std::sort(ord, ord + n, cmp);
        if(w[ord[0]] == w[ord[n - 1]]) {
            puts("0");
            continue;
        }
        DB L = 0, R = 0;
        for(int i = 0; i < n; ++i)
            if(w[i] < w[ord[0]]) {
                int x = a[i] - a[ord[0]], y = b[ord[0]] - b[i];
                if(y < 0) {
                    x = -x;
                    y = -y;
                }
                if(x < 0)
                    x += m;
                R = std::max(R, (DB)x / y);
            }
        while(R - L > eps) {
            DB M = L + (R - L) * 0.5;
            if(check(M))
                R = M;
            else
                L = M;
        }
        int fz = (int)1e6, fm = 1;
        for(int i = 0; i < n; ++i)
            if(w[i] > w[sp]) {
                int x = a[i] - a[sp], y = b[sp] - b[i];
                if(y < 0) {
                    x = -x;
                    y = -y;
                }
                if(x < 0)
                    x += m;
                if((LL)x * fm < (LL)fz * y) {
                    fz = x;
                    fm = y;
                }
            }
        int r = std::__gcd(fz, fm);
        printf("%d/%d\n", fz / r, fm / r);
    }
    return 0;
}
