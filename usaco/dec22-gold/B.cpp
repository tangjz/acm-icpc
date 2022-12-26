#include <bits/stdc++.h>
using namespace std;

typedef unsigned UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;

const int maxn = (int)2e3 + 9, mod = (int)1e9 + 7;
const int maxd = 10, maxc = 26, INF = 0x3f3f3f3f;
const LL maxv = (LL)1e18, INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

struct Point {
    int x, y;
    Point operator - (Point const &t) const {
        return (Point){x - t.x, y - t.y};
    }
    LL det(Point const &t) const {
        return (LL)x * t.y - (LL)y * t.x;
    }
} zero = {};

void prepare() {
}

pair<int, Point> seg[maxn << 1 | 1];
inline int segIdx(int L, int R) {
    return (L + R) | (L < R);
};
void segInit(int L, int R) {
    int rt = segIdx(L, R);
    seg[rt] = {};
    if(L < R) {
        int M = (L + R) >> 1;
        segInit(L, M);
        segInit(M + 1, R);
    }
}
int segAdd(int L, int R, int x, Point const &v) {
    int rt = segIdx(L, R);
    if(L == R) {
        seg[rt] = {1, v};
    } else {
        int M = (L + R) >> 1;
        int lch = x <= M ? segAdd(L, M, x, v) : segIdx(L, M);
        int rch = x <= M ? segIdx(M + 1, R) : segAdd(M + 1, R, x, v);
        if(seg[rch].first) {
            seg[rt] = seg[rch];
            seg[rt].first += seg[lch].first;
        } else {
            seg[rt] = seg[lch];
        }
    }
    return rt;
}
int segDel(int L, int R, int l, Point const &v, bool &stop) {
    // printf("segDel %d %d %d\n", L, R, l);
    int rt = segIdx(L, R);
    if(!seg[rt].first || stop)
        return rt;
    if(L == R) {
        if(seg[rt].second.det(v) > 0) {
            // printf("del %d: %d %d\n", L, seg[rt].second.x, seg[rt].second.y);
            seg[rt] = {};
        } else {
            stop = 1;
        }
    } else {
        int M = (L + R) >> 1;
        int lch = l <= M ? segDel(L, M, l, v, stop) : segIdx(L, M);
        int rch = stop ? segIdx(M + 1, R) : segDel(M + 1, R, l, v, stop);
        if(seg[rch].first) {
            seg[rt] = seg[rch];
            seg[rt].first += seg[lch].first;
        } else {
            seg[rt] = seg[lch];
        }
    }
    return rt;
}
Point const &segAsk(int L, int R, int r) {
    int rt = segIdx(L, R);
    if(!seg[rt].first)
        return zero;
    if(R <= r)
        return seg[rt].second;
    int M = (L + R) >> 1;
    Point const &ret = r > M ? segAsk(M + 1, R, r) : zero;
    return !ret.x ? segAsk(L, M, r) : ret;
}
void solve() {
    int n, q;
    scanf("%d", &n);
    vector<int> h(n), a(n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &h[i]);
    scanf("%d", &q);
    vector<int> ans(q);
    vector<pair<int, int> > eve(q);
    for(int i = 0; i < q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        eve[i] = {--x, y};
    }
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j + 1 < n; ++j) {
            Point las, cur;
            auto rebuild = [&]() {
                // printf("rebuild %d %d\n", i, j);
                segInit(j + 1, n - 1);
                las = zero;
                for(int k = j + 1; k < n; ++k) {
                    cur = (Point){k - j, a[k] - a[j]};
                    if(las.det(cur) >= 0) {
                        // printf("add %d: %d %d\n", k, cur.x, cur.y);
                        segAdd(j + 1, n - 1, k, cur);
                        las = cur;
                    }
                }
            };
            for(int k = j; k < n; ++k)
                a[k] = h[k];
            rebuild();
            int rt = segIdx(j + 1, n - 1);
            for(int k = 0; k < q; ++k) {
                auto &it = eve[k];
                if(it.first >= j) {
                    a[it.first] += it.second;
                    // printf("upd %d: %d\n", it.first, a[it.first]);
                    if(it.first == j) {
                        rebuild();
                    } else {
                        las = segAsk(j + 1, n - 1, it.first);
                        cur = (Point){it.first - j, a[it.first] - a[j]};
                        if(las.det(cur) >= 0) {
                            if(it.first + 1 < n) {
                                bool stop = 0;
                                segDel(j + 1, n - 1, it.first + 1, cur, stop);
                            }
                            // printf("add %d: %d %d\n", it.first, cur.x, cur.y);
                            segAdd(j + 1, n - 1, it.first, cur);
                        }
                    }
                }

                ans[k] += seg[rt].first;
            }
        }
        reverse(h.begin(), h.end());
        for(auto &it: eve)
            it.first = n - 1 - it.first;
    }
    for(int i = 0; i < q; ++i)
        printf("%d\n", ans[i] >> 1);
}

int main() {
    prepare();

    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
