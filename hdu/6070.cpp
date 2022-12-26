#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
typedef double DB;
const int maxn = 60001, maxt = 25;
const DB eps = 1e-12;
int t, n, a[maxn], pos[maxn];
struct Segment {
    DB min, tag;
} seg[maxn << 1 | 1];
inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}
inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}
void seg_init(int L, int R) {
    int rt = seg_idx(L, R);
    seg[rt].min = seg[rt].tag = 0;
    if(L == R)
        return;
    int M = (L + R) >> 1;
    seg_init(L, M);
    seg_init(M + 1, R);
}
void seg_upd(int L, int R, int l, int r, DB x) {
    int rt = seg_idx(L, R);
    if(l <= L && R <= r) {
        seg[rt].min += x;
        seg[rt].tag += x;
        return;
    }
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    if(sgn(seg[rt].tag)) {
        seg[lch].min += seg[rt].tag;
        seg[lch].tag += seg[rt].tag;
        seg[rch].min += seg[rt].tag;
        seg[rch].tag += seg[rt].tag;
        seg[rt].tag = 0;
    }
    if(l <= M)
        seg_upd(L, M, l, r, x);
    if(M < r)
        seg_upd(M + 1, R, l, r, x);
    seg[rt].min = std::min(seg[lch].min, seg[rch].min);
}
DB seg_que(int L, int R, int l, int r) {
    int rt = seg_idx(L, R);
    if(l <= L && R <= r)
        return seg[rt].min;
    int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
    if(sgn(seg[rt].tag)) {
        seg[lch].min += seg[rt].tag;
        seg[lch].tag += seg[rt].tag;
        seg[rch].min += seg[rt].tag;
        seg[rch].tag += seg[rt].tag;
        seg[rt].tag = 0;
    }
    DB ret = 1e20;
    if(l <= M)
        ret = std::min(ret, seg_que(L, M, l, r));
    if(M < r)
        ret = std::min(ret, seg_que(M + 1, R, l, r));
    seg[rt].min = std::min(seg[lch].min, seg[rch].min);
    return ret;
}
bool check(DB lim) {
    DB theta = 1.0 / lim;
    memset(pos + 1, 0, n * sizeof(int));
    seg_init(1, n);
    for(int i = 1; i <= n; ++i) {
        if(pos[a[i]])
            seg_upd(1, n, 1, pos[a[i]], -theta);
        seg_upd(1, n, 1, i, theta - 1);
        pos[a[i]] = i;
        DB res = seg_que(1, n, 1, i);
        if(sgn(res) <= 0)
            return 1;
    }
    return 0;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        DB L = 1.0 / n, R = 1.0;
        for(int i = 0; i < maxt; ++i) {
            DB M = L + (R - L) * 0.5;
            if(check(M))
                R = M;
            else
                L = M;
        }
        printf("%.20f\n", R);
    }
    return 0;
}
