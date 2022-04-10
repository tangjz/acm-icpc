#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxl = 71, maxd = 10;

i64 f[2][maxd + 1][maxl];

void solve() {
    static char buf[maxl];
    scanf("%s", buf);
    int len = strlen(buf);
    int msk = 0;
    for(int i = 1; i < len; ++i) {
        int dt = (int)buf[i - 1] - buf[i];
        if(!dt)
            continue;
        if(dt > 0) {
            msk = 1;
        } else if(msk) {
            puts("-1");
            return;
        }
    }
    i64 ans = 0;
    int las = msk = 0, cur;
    for(int i = 0; i < len; ++i) {
        cur = buf[i] - '0';
        for(int j = 0; j < cur; ++j) {
            if(msk && las < j)
                break;
            ans += f[msk || las > j][j][len - 1 - i];
        }
        msk |= las > cur;
        las = cur;
    }
    printf("%lld\n", ans);
}

int main() {
    for(int i = 0; i < maxd; ++i)
        f[0][i][0] = f[1][i][0] = 1;
    for(int i = 1; i < maxl; ++i)
        for(int j = 0; j < maxd; ++j)
            for(int k = 0; k < maxd; ++k) {
                f[0][j][i] += f[j > k][k][i - 1];
                if(j >= k)
                    f[1][j][i] += f[1][k][i - 1];
            }

    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}