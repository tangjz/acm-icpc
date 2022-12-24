#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10009;
int sgn(LL x) {
    return (x > 0) - (x < 0);
}
struct Point {
    int x, y;
    LL dot(Point const &t) const {
        return (LL)x * t.x + (LL)y * t.y;
    }
    LL det(Point const &t) const {
        return (LL)x * t.y - (LL)y * t.x;
    }
    bool operator < (Point const &t) const {
        if(!y && !t.y && (LL)x * t.x <= 0)
            return x > t.x;
        if(!y && x >= 0 && t.y)
            return 1;
        if(!t.y && t.x >= 0 && y)
            return 0;
        if((LL)y * t.y <= 0)
            return y > t.y;
        LL tmp = det(t);
        return tmp > 0;
    }
    Point operator + (Point const &t) const {
        return (Point){x + t.x, y + t.y};
    }
    Point operator - (Point const &t) const {
        return (Point){x - t.x, y - t.y};
    }
} p[maxn], seg[maxn << 1 | 1], Vec[2];
int t, n, m;
bool vis[maxn];
bool isins(Point A1, Point A2, Point B1, Point B2) {
    return sgn((A2 - A1).det(B1 - A1)) * sgn((A2 - A1).det(B2 - A1)) <= 0
        && sgn((B2 - B1).det(A1 - B1)) * sgn((B2 - B1).det(A2 - B1)) <= 0;
}
pair<LL, LL> lineinsdist(Point A, Point B) {
    Point u = Vec[0] - A, w = B - A;
    LL fz = w.det(u), fm = Vec[1].det(w);
    return fm < 0 ? make_pair(-fz, -fm) : make_pair(fz, fm);
}
struct cmp_sp {
    bool operator () (int const &x, int const &y) {
        pair<LL, LL> dx = lineinsdist(seg[x << 1], seg[x << 1 | 1]), dy = lineinsdist(seg[y << 1], seg[y << 1 | 1]);
        return (__int128)dx.first * dy.second < (__int128)dy.first * dx.second;
    }
};
set<int, cmp_sp> sp;
struct Event {
    int typ, idx;
    Point &point() const {
        return typ ? seg[idx] : p[idx];
    }
    bool operator < (Event const &t) const {
        return point() < t.point() || (!(t.point() < point()) && typ > t.typ);
    }
} event[maxn << 2 | 1];
int main() {
    for(int Case = 1; scanf("%d%d%d", &n, &m, &t) == 3; ++Case) {
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &p[i].x, &p[i].y);
        for(int i = 0; i < m << 1; ++i)
            scanf("%d%d", &seg[i].x, &seg[i].y);
        printf("Case #%d:\n", Case);
        while(t--) {
            int tot = 0, ans = 0;
            scanf("%d%d", &p[n].x, &p[n].y);
            for(int i = 0; i < n; ++i) {
                p[i] = p[i] - p[n];
                event[tot++] = (Event){0, i};
            }
            sp.clear();
            memset(vis, 0, sizeof vis);
            Vec[0] = (Point){0, 0};
            Vec[1] = (Point){(int)3e6, -1};
            for(int i = 0; i < m; ++i) {
                int L = i << 1, R = i << 1 | 1;
                seg[L] = seg[L] - p[n];
                seg[R] = seg[R] - p[n];
                if(!seg[L].det(seg[R]))
                    continue;
                if(seg[R] < seg[L])
                    swap(L, R);
                if(isins(Vec[0], Vec[1], seg[L], seg[R])) {
                    vis[i] = 1;
                    sp.insert(i);
                    event[tot++] = (Event){-1, L};
                    event[tot++] = (Event){1, R};
                } else {
                    event[tot++] = (Event){1, L};
                    event[tot++] = (Event){-1, R};
                }
            }
            sort(event, event + tot);
            for(int i = 0; i < tot; ++i) {
                Vec[1] = event[i].point();
                if(!event[i].typ) {
                    set<int>::iterator it = sp.begin();
                    if(it == sp.end() || !isins(Vec[0], event[i].point(), seg[(*it) << 1], seg[(*it) << 1 | 1]))
                        ++ans;
                } else if(vis[event[i].idx >> 1]) {
                    vis[event[i].idx >> 1] = 0;
                    sp.erase(event[i].idx >> 1);
                } else {
                    vis[event[i].idx >> 1] = 1;
                    sp.insert(event[i].idx >> 1);
                }
            }
            printf("%d\n", ans);
            for(int i = 0; i < n; ++i)
                p[i] = p[i] + p[n];
            for(int i = 0; i < m << 1; ++i)
                seg[i] = seg[i] + p[n];
        }
    }
    return 0;
}