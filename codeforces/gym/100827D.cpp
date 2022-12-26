#include <bits/stdc++.h>
using namespace std;

const int maxn = 201;

void solve() {
    int n, m, a, b, c, d, r;
    scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &r);
    static int seq[maxn], pos[maxn];
    static double f[maxn];
    int com = gcd(n, m);
    n /= com;
    m /= com;
    memset(pos, -1, (m << 1 | 1) * sizeof(int));
    seq[0] = n;
    pos[m + n] = 0;
    for(int i = 1; ; ++i) {
        int &t = seq[i] = seq[i - 1];
        t = (t > 0 ? m : -m) - t - t;
        if(pos[m + t] == -1) {
            pos[m + t] = i;
            continue;
        }
        double k = 1, w = 0; // k x + w
        for(int j = i - 1; j >= 0; --j) {
            int x = seq[j];
            double u = (x > 0 ? d : b) / (double)r + x * x / (double)(m * m);
            double v = (x > 0 ? c : a) / (double)r;
            if(j >= pos[m + t]) {
                k = k * u;
                w = w * u + v;
                if(j == pos[m + t])
                    f[j] = w / (1 - k);
            } else {
                f[j] = u * f[j + 1] + v;
            }
        }
        break;
    }
    printf("%.10f\n", f[0]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
