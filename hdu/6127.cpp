#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 50001;
int t, n, ord[maxn << 1 | 1];
struct Point {
    int x, y, v;
    void read() {
        scanf("%d%d%d", &x, &y, &v);
    }
    LL dot(Point const &t) const {
        return (LL)x * t.x + (LL)y * t.y;
    }
    LL det(Point const &t) const {
        return (LL)x * t.y - (LL)y * t.x;
    }
} p[maxn];
inline int polar_cmp(int const &u, int const &v) {
    Point &a = p[u], &b = p[v];
    if(!a.y && !b.y && (LL)a.x * b.x <= 0)
        return a.x > b.x;
    if(!a.y && a.x >= 0 && b.y)
        return 1;
    if(!b.y && b.x >= 0 && a.y)
        return 0;
    if((LL)a.y * b.y <= 0)
        return a.y > b.y;
    LL tmp = a.det(b);
    return tmp > 0 || (!tmp && a.x < b.x);
}
inline bool check(Point const &a, Point const &b) {
    LL tmp = a.det(b);
    return tmp > 0 || (!tmp && a.dot(b) > 0);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        LL sL = 0, sR = 0, ans = 0;
        for(int i = 0; i < n; ++i) {
            p[i].read();
            ord[i] = i;
            sR += p[i].v;
        }
        std::sort(ord, ord + n, polar_cmp);
        memcpy(ord + n, ord, n * sizeof(int));
        for(int i = 0, j = 0; i < n; ++i) {
            // printf("vec %d %d\n", p[ord[i]].x, p[ord[i]].y);
            for( ; j < n << 1 && check(p[ord[i]], p[ord[j]]); ++j) {
                // printf("add %d %d\n", p[ord[j]].x, p[ord[j]].y);
                sL += p[ord[j]].v;
                sR -= p[ord[j]].v;
            }
            ans = std::max(ans, sL * sR);
            // printf("chk %I64d %I64d : %I64d\n", sL, sR, sL * sR);
            sL -= p[ord[i]].v;
            sR += p[ord[i]].v;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}