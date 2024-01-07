#include <cstdio>
#include <algorithm>
using namespace std;
const int maxm = 1 << 7 | 1;
const char *pat = "23456789TJQKA";
int rnk[maxm], w[maxm];

inline int getCard() {
    static char buf[3];
    scanf("%s", buf);
    return buf[0];
}

inline int calc(int x, int y) {
    return rnk[x] < rnk[y] ? -w[y] : w[x];
}

void solve() {
    static int a[5];
    for(int i = 0; i < 4; ++i)
        a[i] = getCard();
    int ans = -100;
    for(int i = 0; i < 2; ++i) {
        int tmp = 100;
        for(int j = 2; j < 4; ++j) {
            int res = calc(a[i], a[j]);
            if(res > 0) {
                res += calc(a[i ^ 1], a[j ^ 1]);
            } else {
                res -= calc(a[j ^ 1], a[i ^ 1]);
            }
            // printf("%d %d: %d\n", i, j, res);
            tmp = min(tmp, res);
        }
        ans = max(ans, tmp);
    }
    printf("%d\n", ans);
}

int main() {
    for(int i = 0; pat[i]; ++i) {
        int o = pat[i];
        rnk[o] = i;
        w[o] = (i + 1) % 13 + 1;
        // printf("%c: %d %d\n", o, rnk[o], w[o]);
    }
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}