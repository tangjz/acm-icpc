#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, m, p[maxn];
LL a[4][maxn];
pair<int, int> seg[4][maxn << 1 | 1];
inline int seg_idx(int L, int R) {
    return (L + R) | (L < R);
}
inline pair<int, int> seg_merge(LL val[], pair<int, int> lft, pair<int, int> rht) {
    pair<int, int> ret;
    if(val[lft.first] >= val[rht.first]) {
        int x = p[lft.first] != p[rht.first] ? rht.first : rht.second;
        ret = val[lft.second] >= val[x] ? lft : make_pair(lft.first, x);
    } else {
        int x = p[lft.first] != p[rht.first] ? lft.first : lft.second;
        ret = val[rht.second] >= val[x] ? rht : make_pair(rht.first, x);
    }
    return ret;
}
void seg_init(int L, int R) {
    int rt = seg_idx(L, R);
    if(L == R) {
        seg[0][rt] = seg[1][rt] = seg[2][rt] = seg[3][rt] = make_pair(L, 0);
    } else {
        int M = (L + R) >> 1;
        seg_init(L, M);
        seg_init(M + 1, R);
        seg[0][rt] = seg_merge(a[0], seg[0][seg_idx(L, M)], seg[0][seg_idx(M + 1, R)]);
        seg[1][rt] = seg_merge(a[1], seg[1][seg_idx(L, M)], seg[1][seg_idx(M + 1, R)]);
        seg[2][rt] = seg_merge(a[2], seg[2][seg_idx(L, M)], seg[2][seg_idx(M + 1, R)]);
        seg[3][rt] = seg_merge(a[3], seg[3][seg_idx(L, M)], seg[3][seg_idx(M + 1, R)]);
    }
}
void seg_upd(int L, int R, int x) {
    if(L < R) {
        int M = (L + R) >> 1;
        x <= M ? seg_upd(L, M, x) : seg_upd(M + 1, R, x);
        int rt = seg_idx(L, R);
        seg[0][rt] = seg_merge(a[0], seg[0][seg_idx(L, M)], seg[0][seg_idx(M + 1, R)]);
        seg[1][rt] = seg_merge(a[1], seg[1][seg_idx(L, M)], seg[1][seg_idx(M + 1, R)]);
        seg[2][rt] = seg_merge(a[2], seg[2][seg_idx(L, M)], seg[2][seg_idx(M + 1, R)]);
        seg[3][rt] = seg_merge(a[3], seg[3][seg_idx(L, M)], seg[3][seg_idx(M + 1, R)]);
    }
}
void seg_que(int L, int R, int l, int r, pair<int, int> res[4]) {
    if(l <= L && R <= r) {
        int rt = seg_idx(L, R);
        res[0] = seg_merge(a[0], res[0], seg[0][rt]);
        res[1] = seg_merge(a[1], res[1], seg[1][rt]);
        res[2] = seg_merge(a[2], res[2], seg[2][rt]);
        res[3] = seg_merge(a[3], res[3], seg[3][rt]);
    } else {
        int M = (L + R) >> 1;
        if(l <= M)
            seg_que(L, M, l, r, res);
        if(r > M)
            seg_que(M + 1, R, l, r, res);
    }
}
int main() {
    a[0][0] = a[1][0] = a[2][0] = a[3][0] = (LL)-1e15;
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d%d%d", &x, &y, p + i);
            a[0][i] = x + y;
            a[1][i] = x - y;
            a[2][i] = -x + y;
            a[3][i] = -x - y;
        }
        seg_init(1, n);
        printf("Case #%d:\n", Case);
        while(m--) {
            int typ, u, v, w;
            scanf("%d%d%d", &typ, &u, &v);
            if(typ == 1) {
                scanf("%d", &w);
                a[0][u] += v + w;
                a[1][u] += v - w;
                a[2][u] -= v - w;
                a[3][u] -= v + w;
                seg_upd(1, n, u);
            } else if(typ == 2) {
                p[u] = v;
                seg_upd(1, n, u);
            } else {
                pair<int, int> res[4] = {};
                seg_que(1, n, u, v, res);
                LL ans = 0;
                for(int i = 0, j = 3; i < 4; ++i, --j)
                    ans = max(ans, a[i][res[i].first] + a[j][p[res[i].first] != p[res[j].first] ? res[j].first : res[j].second]);
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
