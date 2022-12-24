#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define x first
#define y second
const int maxn = 100001;
int t, rr, cc, n, q, ord[maxn], INF;
pair<int, int> a[maxn], b[maxn];
LL ans[maxn];
struct Segment {
    int cnt, val;
    LL sum;
} segL[maxn << 1 | 1], segR[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}
void seg_init(Segment seg[], int L, int R) {
    Segment &rt = seg[seg_idx(L, R)];
    rt = (Segment){(R - L + 1), rr + 1, (rr + 1) * (R - L + 1LL)};
    if(L == R)
        return;
    int M = (L + R) >> 1;
    seg_init(seg, L, M);
    seg_init(seg, M + 1, R);
}
LL seg_que(Segment seg[], int L, int R, int val) {
    Segment &rt = seg[seg_idx(L, R)];
    if(val <= rt.val)
        return (LL)rt.cnt * val;
    if(L == R)
        return rt.sum;
    int M = (L + R) >> 1;
    Segment &rch = seg[seg_idx(M + 1, R)];
    return seg_que(seg, M + 1, R, val) + (val < rch.val ? seg_que(seg, L, M, val) : rt.sum - rch.sum);
}
void seg_upd(Segment seg[], int L, int R, int x, int val) {
    Segment &rt = seg[seg_idx(L, R)];
    rt.val = val;
    if(L == R) {
        rt.sum = val;
        return;
    }
    int M = (L + R) >> 1;
    Segment &rch = seg[seg_idx(M + 1, R)];
    if(x <= M)
        seg_upd(seg, L, M, x, val);
    else
        seg_upd(seg, M + 1, R, x, val);
    rt.sum = seg_que(seg, L, M, rch.val) + rch.sum;
}
LL seg_que(Segment seg[], int L, int R, int l, int r, int &val) {
    LL ret = 0;
    if(l <= L && R <= r) {
        ret += seg_que(seg, L, R, val);
        val = min(val, seg[seg_idx(L, R)].val);
        return ret;
    }
    int M = (L + R) >> 1;
    if(M < r)
        ret += seg_que(seg, M + 1, R, l, r, val);
    ret += seg_que(seg, L, M, l, r, val);
    return ret;
}
bool cmp(int const &u, int const &v) {
    return b[u] < b[v];
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d%d", &rr, &cc, &n, &q);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &a[i].x, &a[i].y);
        sort(a, a + n);
        for(int i = 0; i < q; ++i) {
            scanf("%d%d", &b[i].x, &b[i].y);
            ord[i] = i;
            ans[i] = 0;
        }
        sort(ord, ord + q, cmp);
        for(int i = 0, j = 0; i < q; ++i) {
            int o = ord[i];
            for( ; j < n && a[j] < b[o]; ++j);
            if(j == n || a[j] != b[o]) {
                int yL = j && a[j - 1].x == b[o].x ? a[j - 1].y : 0;
                int yR = j < n && a[j].x == b[o].x ? a[j].y : cc + 1;
                ans[o] -= yR - yL - 1;
            }
        }
        seg_init(segL, 1, cc);
        seg_init(segR, 1, cc);
        for(int i = q - 1, j = n - 1; i >= 0; --i) {
            int o = ord[i];
            for( ; j >= 0 && a[j].x >= b[o].x; --j) {
                seg_upd(segL, 1, cc, a[j].y, a[j].x);
                seg_upd(segR, 1, cc, cc - a[j].y + 1, a[j].x);
            }
            int cur = segL[seg_idx(b[o].y, b[o].y)].val;
            ans[o] += seg_que(segL, 1, cc, 1, b[o].y, INF = cur);
            if(b[o].y < cc)
                ans[o] += seg_que(segR, 1, cc, 1, cc - b[o].y, INF = cur);
            ans[o] -= (LL)b[o].x * cc;
        }
        for(int i = 0; i < n; ++i)
            a[i].x = rr - a[i].x + 1;
        for(int i = 0; i < q; ++i)
            b[i].x = rr - b[i].x + 1;
        seg_init(segL, 1, cc);
        seg_init(segR, 1, cc);
        for(int i = 0, j = 0; i < q; ++i) {
            int o = ord[i];
            for( ; j < n && a[j].x >= b[o].x; ++j) {
                seg_upd(segL, 1, cc, a[j].y, a[j].x);
                seg_upd(segR, 1, cc, cc - a[j].y + 1, a[j].x);
            }
            int cur = segL[seg_idx(b[o].y, b[o].y)].val;
            ans[o] += seg_que(segL, 1, cc, 1, b[o].y, INF = cur);
            if(b[o].y < cc)
                ans[o] += seg_que(segR, 1, cc, 1, cc - b[o].y, INF = cur);
            ans[o] -= (LL)b[o].x * cc;
        }
        for(int i = 0; i < q; ++i)
            printf("%I64d\n", ans[i]);
    }
    return 0;
}