#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxd = 35;
LL dp[2][maxd][maxd][maxd];

LL F(int s, int d, int i, int j) {
    if(i < 0 || j < 0)
        return 0;
    LL &ret = dp[s][d][i][j];
    if(ret == -1) {
        if(!j) {
            ret = s;
        } else {
            ret = F(s, d, i, j - 1) + F(!s, d, j, i - 1) - F(!s, d, j, i - d);
        }
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, d;
        scanf("%d%d", &n, &d);
        ++d;
        n /= 2;
        LL ans = F(0, d, n, n) - F(0, d, n, n - 1);
        printf("%lld\n", ans << 1);
    }
    return 0;
}
