#include <cmath>
#include <cstdio>
#include <algorithm>
typedef long long LL;
typedef long double DB;
const int maxt = 200001;
const DB pi = acos(-1.0);
int t, r1, r2, n;
DB ans;
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &r1, &r2, &n);
        if(r1 > r2)
            std::swap(r1, r2);
        int fz = (r2 - r1) * r1 * r2, fm = r1 * r2, dt = (r2 - r1) * (r2 - r1);
        ans = 0;
        for(int i = 1; i <= n && i < maxt; ++i) {
            DB up = fz, down = fm + (LL)(i >> 1) * (i >> 1) * dt;
            ans += up * up / (down * down);
        }
        ans *= pi;
        printf("%.5f\n", (double)ans);
    }
    return 0;
}
