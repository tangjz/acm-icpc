#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e4 + 1;

int main() {
    int n, m;
    static int a[maxn], cur = 1, pre = 0;
    static LL f[2][maxn];
    scanf("%d%d", &n, &m);
    a[0] = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        a[i] += a[i - 1];
    }
    function<void(int, int, int, int)> solve = [&](int pL, int pR, int qL, int qR) {
        if(pL > pR)
            return;
        int pM = (pL + pR) / 2, qM = -1;
        for(int q = qL; q <= qR && q < pM; ++q) {
            LL tmp = f[pre][q] + (LL)(pM - q) * (a[pM] - a[q]);
            if(f[cur][pM] > tmp) {
                f[cur][pM] = tmp;
                qM = q;
            }
        }
        solve(pL, pM - 1, qL, qM);
        solve(pM + 1, pR, qM, qR);
    };
    memset(f[cur], 0x3f, (n + 1) * sizeof(LL));
    f[cur][0] = 0;
    for(int i = 1; i <= m; ++i) {
        swap(cur, pre);
        memset(f[cur], 0x3f, (n + 1) * sizeof(LL));
        solve(i, n, i - 1, n - 1);
    }
    printf("%lld\n", f[cur][n]);
    return 0;
}
