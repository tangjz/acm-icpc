#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e3 + 1;

void solve() {
    int n, m;
    LL pL = 0, pR = (LL)-1e15;
    scanf("%d%d", &n, &m);
    while(n--) {
        LL sum = 0, qL = 0, qR = 0;
        static int a[maxn];
        for(int i = 0; i < m; ++i) {
            scanf("%d", a + i);
            sum += a[i];
            qL = max(qL, sum);
            qR = max(qR + a[i], 0LL);
        }
        qL = max(pL + qL, pR + sum);
        qR = max(pR + qR, pL + sum);
        pL = qL;
        pR = qR;
    }
    printf("%lld\n", max(pL, pR));
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    return 0;
}
