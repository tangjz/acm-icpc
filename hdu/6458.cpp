#include <bits/stdc++.h>
typedef long long LL;
int t;
LL n, m, dt;
int main() {
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%lld%lld%lld", &n, &m, &dt);
        LL cur = n - m, idx = -1;
        while(cur < n) {
            LL k = n - cur;
            if(dt > 1)
                k = std::min(k, (cur - idx - 1) / (dt - 1) + 1);
            cur += k;
            if(dt <= cur) {
                (idx += k * dt) >= cur && (idx -= cur);
            } else {
                idx = (idx + dt) % cur;
            }
        }
        printf("Case #%d: %lld\n", Case, idx + 1);
    }
    return 0;
}
