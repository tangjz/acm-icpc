#include <cmath>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = (int)5e3 + 1, maxv = (int)1e6 + 1;

void solve() {
    int n;
    static int tim = 0;
    static pair<int, int> p[maxn], dp[maxv] = {};
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        int &cx = p[i].first, &cy = p[i].second;
        scanf("%d%d", &cx, &cy);
    }
    int &sx = p[0].first, &sy = p[0].second;
    int &tx = p[n - 1].first, &ty = p[n - 1].second;
    dp[sx] = make_pair(0, ++tim);
    for(int i = 0; i < n; ++i) {
        int &cx = p[i].first, &cy = p[i].second;
        LL upp2 = (LL)cy * cy - (LL)(cy - sy) * (LL)(cy - sy);
        int upp = sqrtl(upp2);
        for( ; (LL)upp * upp <= upp2; ++upp);
        for(int px = cx - 1, nx = min(cx + 1, tx), dx = 1; px >= sx && dx < upp; --px, nx < tx && (++nx), ++dx) {
            if(dp[px].second != tim)
                continue;
            if(dp[nx].second != tim)
                dp[nx] = make_pair(INT_MAX, tim);
            dp[nx].first = min(dp[nx].first, dp[px].first + 1);
        }
    }
    if(dp[tx].second != tim) {
        puts("-1");
    } else {
        printf("%d\n", dp[tx].first);
    }
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}