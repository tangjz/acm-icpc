#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

void solve() {
    int n, m, sz[2] = {};
    static int que[maxn], f[2][maxn];
    static pair<int, int> a[maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
        a[i].first = -a[i].first;
        que[i] = a[i].second;
    }
	sort(a, a + n);
    sort(que, que + n);
    m = unique(que, que + n) - que;
    for(int i = 0; i < n; ++i) {
        int u = lower_bound(que, que + m, a[i].second) - que;
        for(int j = 0; j < 2; ++j) {
            int p = upper_bound(f[j], f[j] + sz[j], u) - f[j];
            if(p == sz[j]) {
                f[j][sz[j]++] = u;
                break;
            }
            swap(f[j][p], u);
        }
    }
    printf("%d\n", sz[0] + sz[1]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1, n; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
