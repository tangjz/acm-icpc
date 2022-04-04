#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = (int)1e3 + 1;
const double pi = acos(-1), eps = 1e-9;

int n;
struct Circle {
    int x, y, r, sgn;
} c[maxn];

inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

inline bool lessComp(double const &u, double const &v) {
    return dcmp(u - v) < 0;
}

inline bool equalComp(double const &u, double const &v) {
    return !dcmp(u - v);
}

inline double fixed_angle(double x) {
    dcmp(x) < 0 && (x += pi * 2);
    dcmp(x - pi * 2) >= 0 && (x -= pi * 2);
    return x;
}

double solve() {
    int m;
    scanf("%d", &m);
    vector<vector<int> > rings(m, vector<int>(4));
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < 4; ++j)
            scanf("%d", &rings[i][j]);
        int d1 = rings[i][2], d2 = rings[i][3];
        rings[i][2] = max(d1 - d2, 0);
        rings[i][3] = d1 + d2;
    }
    sort(rings.begin(), rings.end());
    n = 0;
    for(int i = 0; i < m; ++i) {
        int x = rings[i][0], y = rings[i][1];
        int L = rings[i][2], R = rings[i][3];
        while(i + 1 < m && rings[i + 1][0] == x && rings[i + 1][1] == y && rings[i + 1][2] <= R)
            R = max(R, rings[++i][3]);
        // fprintf(stderr, "ring (%d, %d) [%d, %d]\n", x, y, L, R);
        if(L > 0)
            c[n++] = (Circle){x, y, L, -1};
        c[n++] = (Circle){x, y, R, 1};
    }
    double ans = 0;
    for(int i = 0; i < n; ++i) {
        int tot = 0, adt = c[i].sgn < 0 ? -1 : 0;
        static int ctr[maxn << 1 | 1];
        static double que[maxn << 1 | 1];
        static pair<int, pair<double, double> > seq[maxn];
        for(int j = 0; j < n; ++j) {
            if(i == j)
                continue;
            int dx = c[j].x - c[i].x;
            int dy = c[j].y - c[i].y;
            int dr = c[j].r - c[i].r, sr = c[j].r + c[i].r;
            int dist2 = dx * dx + dy * dy;
            if(dist2 >= sr * sr)
                continue;
            if(dist2 <= dr * dr) {
                if(dr > 0)
                    adt += c[j].sgn;
                continue;
            }
            double rad = atan2(dy, dx);
            double delta = acos((dist2 + c[i].r * c[i].r - c[j].r * c[j].r) / (2 * c[i].r * sqrtl(dist2)));
            que[tot << 1] = fixed_angle(rad - delta);
            que[tot << 1 | 1] = fixed_angle(rad + delta);
            seq[tot] = {c[j].sgn, {que[tot << 1], que[tot << 1 | 1]}};
            ++tot;
        }
        sort(que, que + tot * 2, lessComp);
        m = unique(que, que + tot * 2, equalComp) - que;
        que[m] = que[0];
        memset(ctr, 0, m * sizeof(int));
        for(int j = 0; j < tot; ++j) {
            int L = lower_bound(que, que + m, seq[j].second.first, lessComp) - que;
            int R = lower_bound(que, que + m, seq[j].second.second, lessComp) - que;
            ctr[L] += seq[j].first;
            ctr[R] -= seq[j].first;
            if(L > R)
                adt += seq[j].first;
        }
        // fprintf(stderr, "circle (%d, %d) %d (%d):\n", c[i].x, c[i].y, c[i].r, c[i].sgn);
        double sx = 0, sy = 0, sr = 0;
        for(int j = 0; j < m; ++j) {
            if(j > 0)
                ctr[j] += ctr[j - 1];
            assert(ctr[j] + adt >= 0);
            if(ctr[j] + adt > 0)
                continue;
            double L = que[j], R = que[j + 1];
            // fprintf(stderr, "[%.4f, %.4f]\n", L, R);
            sx += cos(R) - cos(L);
            sy += sin(R) - sin(L);
            sr += R - L;
            if(!lessComp(L, R))
                sr += pi * 2;
        }
        if(!m && !adt) {
            // fprintf(stderr, "[%.4f, %.4f]\n", 0.0, 2 * pi);
            sr = pi * 2;
        }
        ans += c[i].sgn * c[i].r * (c[i].x * sy - c[i].y * sx + c[i].r * sr) / 2;
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        printf("Case %d: %.10f\n", Case, solve());
    return 0;
}