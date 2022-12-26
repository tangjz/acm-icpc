#include <bits/stdc++.h>
using namespace std;
const int maxv = 101, maxn = (int)1e4 + maxv + 10;
inline void upd_min(int &x, int y) {
    x > y && (x = y);
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m, ans = INT_MAX;
        scanf("%d%d", &n, &m);
        while(n--) {
            int x, y;
            scanf("%d%d", &x, &y);
            upd_min(ans, ((m - 1) / x + 1) * y);
        }
        printf("%d\n", ans);
    }
    return 0;
}
