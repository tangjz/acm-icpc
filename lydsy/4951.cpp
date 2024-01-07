#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<int, int> Point;
typedef long long LL;
const int maxn = 500001, INF = 0x3f3f3f3f;
int n, m;
Point a[maxn], b[maxn];
LL f[maxn], ans;
inline bool upd(LL &x, LL y) {
    return x < y ? (x = y, 1) : 0;
}
void solve(int L, int R, int dL, int dR) {
    if(L > R)
        return;
    int M = (L + R) >> 1, dM;
    for(int i = dL; i <= dR; ++i) {
		if(b[i].first < a[M].first)
			continue;
        LL val = (LL)(b[i].first - a[M].first) * (b[i].second - a[M].second);
        if(upd(f[M], val))
            dM = i;
    }
    upd(ans, f[M]);
    solve(L, M - 1, dL, dM);
    solve(M + 1, R, dM, dR);
}
int main() {
    int tp;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &a[i].first, &a[i].second);
    for(int i = 0; i < m; ++i)
        scanf("%d%d", &b[i].first, &b[i].second);
    sort(a, a + n);
    tp = 0;
    for(int i = 0, x, y = INF; i < n; ) {
        if(a[i].second < y) {
            f[tp] = -(LL)INF * INF;
            a[tp++] = a[i];
            y = a[i].second;
        }
        for(x = a[i].first; i < n && a[i].first == x; ++i);
    }
    n = tp;
    sort(b, b + m, greater<Point>());
    tp = 0;
    for(int i = 0, x, y = 0; i < m; ) {
        if(b[i].second > y) {
            b[tp++] = b[i];
            y = b[i].second;
        }
        for(x = b[i].first; i < m && b[i].first == x; ++i);
    }
    m = tp;
    reverse(b, b + m);
    solve(0, n - 1, 0, m - 1);
    printf("%lld\n", ans);
    return 0;
}