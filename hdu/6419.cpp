#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 209;
const DB pi = acos(-1.0), eps = 1e-3, INF = 1e10;
inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}
int t, n, m, rad, otot, btot, ord[maxn];
DB ans[maxn];
struct Point {
    DB x, y;
    void read() {
        int _x, _y;
        scanf("%d%d", &_x, &_y);
        x = _x;
        y = _y;
    }
    Point operator + (Point const &t) const {
        return (Point){x + t.x, y + t.y};
    }
    Point operator - (Point const &t) const {
        return (Point){x - t.x, y - t.y};
    }
    Point operator * (DB const &t) const {
        return (Point){x * t, y * t};
    }
    Point shiftLeft() const {
        return (Point){-y, x};
    }
    DB det(Point const &t) const {
        return x * t.y - y * t.x;
    }
    DB dot(Point const &t) const {
        return x * t.x + y * t.y;
    }
    DB len() const {
        return sqrtl(dot(*this));
    }
    DB angle() const {
        return atan2(y, x);
    }
} p[maxn], q[maxn], seq[maxn << 2 | 1];
struct Segment {
    Point u, v;
    bool contains(Point const &p) const {
        Point lft = u - p;
        Point rht = v - p;
        return sgn(lft.det(rht)) == 0 && sgn(lft.dot(rht)) <= 0;
    }
} a[maxn];
inline bool isInside(DB L, DB R, DB p) {
    if(sgn(L - R) <= 0)
        return sgn(L - p) <= 0 && sgn(p - R) <= 0;
    return sgn(p - R) <= 0 || sgn(L - p) <= 0;
}
struct Sector {
    Point c, u, v;
    bool contains(Point const &p) const {
        return sgn((u - c).det(p - c)) >= 0 && sgn((v - c).det(p - c)) <= 0;
    }
} b[maxn];
bool getFootPoint(Segment p, Point q, Point &res) {
    res = p.v - p.u;
    res = p.u + res * (res.dot(q - p.u) / res.dot(res));
    return p.contains(res);
}
bool getIntersection(Segment p, Segment q, Point &res) {
    Point vec1 = p.v - p.u;
    Point vec2 = q.v - q.u;
    DB area = vec1.det(vec2);
    if(sgn(area) == 0)
        return 0;
    int s1 = sgn(vec1.det(q.u - p.u));
    int s2 = sgn(vec1.det(q.v - p.u));
    int s3 = sgn(vec2.det(p.u - q.u));
    int s4 = sgn(vec2.det(p.v - q.u));
    if(s1 * s2 >= 0 || s3 * s4 >= 0)
        return 0;
    res = p.u + vec1 * (vec2.det(p.u - q.u) / area);
    return 1;
}
bool getFootPoint(Sector p, Point q, Point &res) {
    Point vec = q - p.c;
    if(sgn(vec.len()) == 0 || sgn(vec.len() - rad) > 0)
        return 0;
    res = p.c + vec * (rad / vec.len());
    return p.contains(res);
}
int getIntersection(Sector p, Segment q, Point res[]) {
    Point mid;
    getFootPoint(q, p.c, mid);
    DB dis2 = (mid - p.c).dot(mid - p.c);
    int s = sgn(dis2 - (LL)rad * rad);
    if(s > 0)
        return 0;
    if(s == 0) {
        res[0] = mid;
        return p.contains(res[0]) && q.contains(res[0]);
    }
    DB adt = sqrtl((LL)rad * rad - dis2);
    Point vec = q.v - q.u;
    vec = vec * (adt / vec.len());
    int cnt = 0;
    if(p.contains(res[cnt] = mid - vec) && q.contains(res[cnt]))
        ++cnt;
    if(p.contains(res[cnt] = mid + vec) && q.contains(res[cnt]))
        ++cnt;
    return cnt;
}
int getIntersection(Sector p, Sector q, Point res[]) {
    Point vec = q.c - p.c;
    DB dis2 = vec.dot(vec);
    int s = sgn(dis2 - 4LL * rad * rad);
    if(s > 0)
        return 0;
    Point mid = p.c + vec * 0.5;
    if(s == 0) {
        res[0] = mid;
        return p.contains(res[0]) && q.contains(res[0]);
    }
    DB adt = sqrtl((LL)rad * rad - dis2 / 4);
    vec = vec.shiftLeft() * (adt / vec.len());
    int cnt = 0;
    if(p.contains(res[cnt] = mid - vec) && q.contains(res[cnt]))
        ++cnt;
    if(p.contains(res[cnt] = mid + vec) && q.contains(res[cnt]))
        ++cnt;
    return cnt;
}
bool isValid(Point u) {
    DB dis = INF;
    bool odd = 0;
    for(int i = 0; i < n; ++i) {
        int rht = i + 1 < n ? i + 1 : 0;
        dis = min(dis, (u - p[i]).len());
        Point tmp;
        if(getFootPoint((Segment){p[i], p[rht]}, u, tmp))
            dis = min(dis, (u - tmp).len());
        int s1 = sgn(p[i].y - u.y), s2 = sgn(p[rht].y - u.y);
        if((s1 < 0 && s2 >= 0) || (s1 >= 0 && s2 < 0)) {
            DB x = p[i].x + (p[rht].x - p[i].x) / (p[rht].y - p[i].y) * (u.y - p[i].y);
            odd ^= sgn(x - u.x) < 0;
        }
    }
    return sgn(dis - rad) >= 0 && odd;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &rad);
        for(int i = 0; i < n; ++i)
            p[i].read();
        otot = 0;
        for(int i = 0; i < m; ++i) {
            q[i].read();
            if(isValid(q[i])) {
                ans[i] = 0;
            } else {
                ans[i] = INF;
                ord[otot++] = i;
            }
        }
        for(int i = 0; i < n; ++i) {
            int rht = i + 1 < n ? i + 1 : 0;
            Point vec = (p[rht] - p[i]).shiftLeft();
            vec = vec * (rad / vec.len());
            a[i] = (Segment){p[i] + vec, p[rht] + vec};
            int cnt = 0;
            if(isValid(seq[cnt] = a[i].u))
                ++cnt;
            if(isValid(seq[cnt] = a[i].v))
                ++cnt;
            for(int j = 0; j < i; ++j)
                if(getIntersection(a[i], a[j], seq[cnt]) && isValid(seq[cnt]))
                    ++cnt;
            for(int j = 0; j < otot; ++j) {
                int o = ord[j];
                bool adt = getFootPoint(a[i], q[o], seq[cnt]) && isValid(seq[cnt]);
                for(int k = 0; k < cnt + adt; ++k)
                    ans[o] = min(ans[o], (seq[k] - q[o]).len());
            }
        }
        btot = 0;
        for(int i = 0; i < n; ++i) {
            int lft = i - 1 < 0 ? n - 1 : i - 1;
            int rht = i + 1 < n ? i + 1 : 0;
            if(sgn((p[i] - p[lft]).det(p[rht] - p[i])) >= 0)
                continue;
            b[btot] = (Sector){p[i], a[i].u, a[lft].v};
            int cnt = 0;
            static Point que[3];
            for(int j = 0; j < n; ++j) {
                int adt = getIntersection(b[btot], a[j], que);
                for(int k = 0; k < adt; ++k)
                    if(isValid(seq[cnt] = que[k]))
                        ++cnt;
            }
            for(int j = 0; j < btot; ++j) {
                int adt = getIntersection(b[btot], b[j], que);
                for(int k = 0; k < adt; ++k)
                    if(isValid(seq[cnt] = que[k]))
                        ++cnt;
            }
            for(int j = 0; j < m; ++j) {
                int o = ord[j];
                bool adt = getFootPoint(b[btot], q[o], seq[cnt]) && isValid(seq[cnt]);
                for(int k = 0; k < cnt + adt; ++k)
                    ans[o] = min(ans[o], (seq[k] - q[o]).len());
            }
            ++btot;
        }
        for(int i = 0; i < m; ++i)
            printf("%.0f\n", ans[i]);
    }
    return 0;
}