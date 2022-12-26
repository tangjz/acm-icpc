#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int t, n, m, mod, ans;
int main() {
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d%d", &n, &m, &mod);
        m = min(n, m);
        ans = n - m + 1;
        for(int i = 1; i <= m; ++i)
            ans += n - m;
        ans -= m < n;
        for(int i = m + 1; i <= n; ++i) {
            ans += n - i;
            ans += n - i;
            ans -= i < n;
        }
        for(int i = 1; i <= m; ++i)
            ans = (LL)ans * i % mod;
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
