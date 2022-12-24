#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 101;
const DB eps = 1e-12, pi = acos(-1.0);
int t, n, m, R, ctr[maxn << 2 | 1];
DB que[maxn << 2 | 1];
pair<DB, DB> seg[maxn];
inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}
inline bool eq(DB x, DB y) {
    return !sgn(x - y);
}
inline bool les(DB x, DB y) {
    return sgn(x - y) < 0;
}
inline DB cos_fix(DB value) {
    return max(min(value, (DB)1), (DB)-1);
}
inline DB ang_fix(DB angle) {
    if(sgn(angle + pi) <= 0)
        angle += pi * 2;
    if(sgn(angle - pi) > 0)
        angle -= pi * 2;
    return angle;
}
DB solve() {
    scanf("%d%d", &n, &R);
    m = 0;
    for(int i = 0; i < n; ++i) {
        int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
        int dis2 = x * x + y * y;
        if(dis2 <= (R - r) * (R - r) || dis2 >= (R + r) * (R + r))
            continue;
        DB angle = atan2(y, x), delta = acos(cos_fix((R * R + dis2 - r * r) / (2 * R * sqrtl(dis2))));
        seg[m++] = make_pair(ang_fix(angle - delta), ang_fix(angle + delta));
    }
    if(!m)
        return R + R;
    n = m;
    m = 0;
    for(int i = 0; i < n; ++i) {
        que[m++] = seg[i].first;
        que[m++] = seg[i].second;
    }
    sort(que, que + m);
    m = unique(que, que + m, eq) - que;
    memset(ctr, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i) {
        int pL = lower_bound(que, que + m, seg[i].first, les) - que;
        int pR = lower_bound(que, que + m, seg[i].second, les) - que;
        if(pL < pR) {
            ++ctr[pL];
            --ctr[pR];
        } else {
            ++ctr[0];
            --ctr[pR];
            ++ctr[pL];
            --ctr[m];
        }
    }
    for(int i = 1; i < m; ++i)
        ctr[i] += ctr[i - 1];
    for(int i = 0; i < m; ++i) {
        ctr[m + i] = ctr[i];
        que[m + i] = que[i] + pi * 2;
    }
    DB ans = 0;
    for(int i = 0, j = 0; i < m; ++i) {
        DB ang = que[i] + pi;
        for( ; j < i + m && les(que[j], ang); ++j);
        if((j < i + m && eq(que[j], ang)) || !ctr[j - 1])
            return R + R;
        ans = max(ans, que[j - 1] - que[i]);
    }
    return (R + R) * sin(ans / 2);
}
int main() {
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case)
        printf("Case #%d: %.20f\n", Case, (double)solve());
    return 0;
}