#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1.0);
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, R;
        scanf("%d%d", &n, &R);
        DB ans = 0, rem = pi;
        for(int i = 1; i <= n; ++i) {
            int x, y, r;
            scanf("%d%d%d", &x, &y, &r);
            int dis2 = x * x + y * y;
            if(dis2 < (R - r) * (R - r) || dis2 > (R + r) * (R + r))
                continue;
            DB dis = sqrtl(dis2);
            DB ang1 = acos(min(max((dis2 + R * R - r * r) / (2 * R * dis), -1.0), 1.0));
            DB ang2 = acos(min(max((dis2 - R * R + r * r) / (2 * r * dis), -1.0), 1.0));
            rem -= ang1;
            ans += 2 * r * ang2;
        }
        ans += 2 * R * rem;
        printf("%.20f\n", ans);
    }
    return 0;
}