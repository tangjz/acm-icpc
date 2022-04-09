#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = (int)1e5 + 1;

struct Point {
    int x, y;
    Point operator - (const Point &t) const {
        return (Point){x - t.x, y - t.y};
    }
    i64 det(const Point &t) const {
        return (i64)x * t.y - (i64)y * t.x;
    }
} ;

void solve() {
    int n, fir = 0;
    static Point p[maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
        if(make_pair(p[fir].x, p[fir].y) > make_pair(p[i].x, p[i].y))
            fir = i;
    }
    rotate(p, p + fir, p + n);
    if((p[1] - p[0]).det(p[n - 1] - p[0]) < 0)
        reverse(p + 1, p + n);
    int ans = 0;
    for(int i = 0, j = 1, k = 2; i < n; ++i, j = k, (++k) == n && (k = 0))
        ans += (p[j] - p[i]).det(p[k] - p[j]) < 0;
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
