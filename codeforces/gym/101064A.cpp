#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

inline int sgn(double x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    double x[5], y[5];
    for(int i = 0; i < 5; ++i)
        scanf("%lf%lf", x + i, y + i);
    swap(x[0], y[0]);
    double c00 = (x[2] - x[1]) / x[0] - 1, c01 = (x[4] - x[1]) / y[0], c02 = -x[1];
    double c10 = (y[2] - y[1]) / x[0], c11 = (y[4] - y[1]) / y[0] - 1, c12 = -y[1];
    double det = c00 * c11 - c01 * c10;
    if(sgn(det)) {
        double px = (c11 * c02 - c01 * c12) / det;
        double py = (c00 * c12 - c10 * c02) / det;
        printf("%.10f %.10f\n", px, py);
        return;
    }
    if(!sgn(c00) && !sgn(c01)) {
        puts("0 0");
        return;
    }
    for(int i = 1, j = 4; i < 5; j = i++) {
        double c20 = y[i] - y[j], c21 = x[j] - x[i], c22 = c20 * x[j] + c21 * y[j];
        double det = c00 * c21 - c01 * c20;
        if(!sgn(det))
            continue;
        double px = (c21 * c02 - c01 * c22) / det;
        double py = (c00 * c22 - c20 * c02) / det;
        double pk = sgn(c20) ? (py - y[j]) / c20 : (x[j] - px) / c21;
        if(sgn(pk) < 0 || sgn(pk - 1) > 0)
            continue;
        printf("%.10f %.10f\n", px, py);
        return;
    }
    puts("???");
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
