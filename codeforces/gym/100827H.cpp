#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e3 + 1, maxm = 11;

void solve() {
    int n, m, ans = -1;
    static int a[maxm], b[maxm], f[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i)
        scanf("%d", a + i);
    sort(a, a + m);
    memset(f, -1, n * sizeof(int));
    f[n] = 0;
    for(int i = 1, upp = n; upp > 0; ++i) {
        for(int j = 0; j < m; ++j)
            b[j] = a[j] * i;
        for(int j = 0; j <= upp; ++j) {
            f[j] = -1;
            for(int k = 0; k < m && j + b[k] <= upp; ++k) {
                int jj = j + b[k];
                if(f[jj] != -1)
                    f[j] = max(f[j], f[jj] + a[k]);
            }
        }
        ans = max(ans, f[0]);
        for( ; upp > 0 && f[upp] == -1; --upp);
    }
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
